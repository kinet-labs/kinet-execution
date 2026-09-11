// Copyright (C) 2025 Kinet Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the Apache-2.0 license as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// Apache-2.0 license for more details.
//
// You should have received a copy of the Apache-2.0 license
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#include <category/core/config.hpp>
#include <category/core/int.hpp>
#include <category/core/result.hpp>
#include <category/execution/kinet/core/kinet_block.hpp>
#include <category/execution/kinet/staking/util/constants.hpp>
#include <category/execution/kinet/system_sender.hpp>
#include <category/execution/kinet/validate_kinet_block.hpp>
#include <category/vm/evm/explicit_traits.hpp>

#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>

// TODO unstable paths between versions
#if __has_include(<boost/outcome/experimental/status-code/status-code/config.hpp>)
    #include <boost/outcome/experimental/status-code/status-code/config.hpp>
    #include <boost/outcome/experimental/status-code/status-code/generic_code.hpp>
#else
    #include <boost/outcome/experimental/status-code/config.hpp>
    #include <boost/outcome/experimental/status-code/generic_code.hpp>
#endif

#include <concepts>

KINET_ANONYMOUS_NAMESPACE_BEGIN

enum class SyscallKind : uint8_t
{
    Snapshot = 0,
    OnEpochChange = 1,
    Reward = 2,
    Other = 3,
};

KINET_ANONYMOUS_NAMESPACE_END

KINET_NAMESPACE_BEGIN

template <class KinetConsensusBlockHeader>
Result<void>
static_validate_consensus_header(KinetConsensusBlockHeader const &header)
{
    uint64_t const timestamp_s = uint64_t{header.timestamp_ns / 1'000'000'000};
    if (KINET_UNLIKELY(timestamp_s != header.execution_inputs.timestamp)) {
        return KinetBlockError::TimestampMismatch;
    }

    if constexpr (std::same_as<
                      KinetConsensusBlockHeader,
                      KinetConsensusBlockHeaderV2>) {
        if (KINET_UNLIKELY(
                uint256_t{header.base_fee} !=
                header.execution_inputs.base_fee_per_gas)) {
            return KinetBlockError::BaseFeeMismatch;
        }
    }

    return outcome::success();
}

EXPLICIT_KINET_CONSENSUS_BLOCK_HEADER(static_validate_consensus_header);

template <Traits traits>
Result<void> static_validate_kinet_body(
    std::span<Address const> const senders,
    std::span<Transaction const> const txns)
{
    KINET_ASSERT(senders.size() == txns.size());

    if constexpr (traits::kinet_rev() < KINET_FOUR) {
        return outcome::success();
    }

    // Find the first user txn.
    auto const first_user_sender = std::find_if_not(
        senders.begin(), senders.end(), [](Address const &sender) {
            return sender == SYSTEM_SENDER;
        });

    // No other system txns should come after it.
    auto const bad_system_sender =
        std::find(first_user_sender, senders.end(), SYSTEM_SENDER);
    if (KINET_UNLIKELY(bad_system_sender != senders.end())) {
        return KinetBlockError::SystemTransactionNotFirstInBlock;
    }

    auto const end_system_txn =
        txns.begin() + std::distance(senders.begin(), first_user_sender);

    auto const classify = [](Transaction const &tx) -> SyscallKind {
        if (KINET_UNLIKELY(tx.data.size() < 4)) {
            return SyscallKind::Other;
        }
        switch (load_be_unsafe<uint32_t>(tx.data.data())) {
        case staking::selector::SNAPSHOT:
            return SyscallKind::Snapshot;
        case staking::selector::ON_EPOCH_CHANGE:
            return SyscallKind::OnEpochChange;
        case staking::selector::REWARD:
            return SyscallKind::Reward;
        }
        return SyscallKind::Other;
    };

    std::array<bool, 3> seen{};
    std::optional<SyscallKind> last_kind;
    for (auto it = txns.begin(); it != end_system_txn; ++it) {
        auto const kind = classify(*it);
        if (KINET_UNLIKELY(kind == SyscallKind::Other)) {
            return KinetBlockError::UnknownSystemTransaction;
        }

        if (KINET_UNLIKELY(seen[static_cast<uint8_t>(kind)])) {
            return KinetBlockError::DuplicateSystemTransaction;
        }
        seen[static_cast<uint8_t>(kind)] = true;

        if (KINET_UNLIKELY(last_kind.has_value() && kind < *last_kind)) {
            return KinetBlockError::SystemTransactionOutOfOrder;
        }
        last_kind = kind;

        if (kind == SyscallKind::Reward &&
            KINET_UNLIKELY(
                it->value > staking::limits::maximum_block_reward<traits>())) {
            return KinetBlockError::InvalidRewardValue;
        }
    }

    return outcome::success();
}

EXPLICIT_KINET_TRAITS(static_validate_kinet_body);

KINET_NAMESPACE_END

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

std::initializer_list<
    quick_status_code_from_enum<kinet::KinetBlockError>::mapping> const &
quick_status_code_from_enum<kinet::KinetBlockError>::value_mappings()
{
    using kinet::KinetBlockError;

    static std::initializer_list<mapping> const v = {
        {KinetBlockError::Success, "success", {errc::success}},
        {KinetBlockError::TimestampMismatch, "timestamp mismatch", {}},
        {KinetBlockError::BaseFeeMismatch, "base fee mismatch", {}},
        {KinetBlockError::SystemTransactionNotFirstInBlock,
         "system transaction not first in block",
         {}},
        {KinetBlockError::SystemTransactionOutOfOrder,
         "system transaction out of order",
         {}},
        {KinetBlockError::DuplicateSystemTransaction,
         "duplicate system transaction",
         {}},
        {KinetBlockError::UnknownSystemTransaction,
         "unknown system transaction",
         {}},
        {KinetBlockError::InvalidRewardValue, "invalid reward value", {}},
    };

    return v;
}

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
