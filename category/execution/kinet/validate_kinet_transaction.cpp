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
#include <category/core/likely.h>
#include <category/execution/ethereum/state3/state.hpp>
#include <category/execution/ethereum/transaction_gas.hpp>
#include <category/execution/ethereum/validate_transaction.hpp>
#include <category/execution/kinet/system_sender.hpp>
#include <category/execution/kinet/validate_kinet_transaction.hpp>
#include <category/vm/evm/explicit_traits.hpp>

#include <boost/outcome/success_failure.hpp>

#include <ranges>
#include <system_error>

KINET_NAMESPACE_BEGIN

template <Traits traits>
Result<void> validate_transaction(
    Transaction const &tx, Address const &sender, State &state,
    uint256_t const &base_fee_per_gas,
    std::span<std::optional<Address> const> const authorities,
    trace::StateTracer &state_tracer)
{
    auto res =
        validate_ethereum_transaction<traits>(tx, sender, state, state_tracer);
    if constexpr (traits::kinet_rev() >= KINET_FOUR) {
        if (res.has_error() &&
            res.error() != TransactionError::InsufficientBalance) {
            return res;
        }

        uint256_t const gas_fee =
            uint256_t{tx.gas_limit} * gas_price<traits>(tx, base_fee_per_gas);
        if (KINET_UNLIKELY(state.get_balance(sender) < gas_fee)) {
            return KinetTransactionError::InsufficientBalanceForFee;
        }

        if (KINET_UNLIKELY(std::ranges::contains(authorities, SYSTEM_SENDER))) {
            return KinetTransactionError::SystemTransactionSenderIsAuthority;
        }
    }
    else {
        return res;
    }
    return outcome::success();
}

EXPLICIT_KINET_TRAITS(validate_transaction);

KINET_NAMESPACE_END

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

std::initializer_list<
    quick_status_code_from_enum<kinet::KinetTransactionError>::mapping> const &
quick_status_code_from_enum<kinet::KinetTransactionError>::value_mappings()
{
    using kinet::KinetTransactionError;

    static std::initializer_list<mapping> const v = {
        {KinetTransactionError::Success, "success", {errc::success}},
        {KinetTransactionError::InsufficientBalanceForFee,
         "insufficient balance for fee",
         {}},
        {KinetTransactionError::SystemTransactionSenderIsAuthority,
         "system transaction sender is authority",
         {}},
    };

    return v;
}

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
