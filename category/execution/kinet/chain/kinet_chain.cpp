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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <category/core/config.hpp>
#include <category/core/likely.h>
#include <category/core/result.hpp>
#include <category/execution/ethereum/chain/ethereum_mainnet.hpp>
#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/ethereum/execute_transaction.hpp>
#include <category/execution/ethereum/precompiles.hpp>
#include <category/execution/ethereum/state2/block_state.hpp>
#include <category/execution/ethereum/state3/state.hpp>
#include <category/execution/ethereum/transaction_gas.hpp>
#include <category/execution/ethereum/validate_block.hpp>
#include <category/execution/ethereum/validate_transaction.hpp>
#include <category/execution/kinet/chain/kinet_chain.hpp>
#include <category/execution/kinet/kinet_precompiles.hpp>
#include <category/execution/kinet/reserve_balance.h>
#include <category/execution/kinet/reserve_balance.hpp>
#include <category/execution/kinet/system_sender.hpp>
#include <category/execution/kinet/validate_kinet_transaction.hpp>
#include <category/vm/evm/explicit_traits.hpp>

namespace
{
    using namespace kinet;

    static ankerl::unordered_dense::segmented_set<Address> const
        empty_senders_and_authorities{};
    static std::vector<Address> const empty_senders{Address{0}};
    static std::vector<std::vector<std::optional<Address>>> const
        empty_authorities{{}};
}

KINET_NAMESPACE_BEGIN

using BOOST_OUTCOME_V2_NAMESPACE::success;

kinet_eth_revision KinetChain::get_revision(
    uint64_t /*block_number*/, uint64_t const timestamp) const
{
    auto const kinet_revision = get_kinet_revision(timestamp);

    if (KINET_LIKELY(kinet_revision >= KINET_FOUR)) {
        return KINET_ETH_PRAGUE;
    }

    return KINET_ETH_CANCUN;
}

BlobSchedule KinetChain::get_blob_schedule(uint64_t /*timestamp*/) const
{
    return KINET_BLOB_SCHEDULE;
}

template <typename T>
    requires is_kinet_trait_v<T>
ChainContext<T> ChainContext<T>::debug_empty()
{
    return ChainContext<T>{
        .grandparent_senders_and_authorities = empty_senders_and_authorities,
        .parent_senders_and_authorities = empty_senders_and_authorities,
        .senders_and_authorities = empty_senders_and_authorities,
        .senders = empty_senders,
        .authorities = empty_authorities};
}

EXPLICIT_KINET_TRAITS_STRUCT(ChainContext);

ankerl::unordered_dense::segmented_set<Address> combine_senders_and_authorities(
    std::span<Address const> const senders,
    std::span<std::vector<std::optional<Address>> const> const authorities)
{
    ankerl::unordered_dense::segmented_set<Address> senders_and_authorities;

    for (Address const &sender : senders) {
        senders_and_authorities.insert(sender);
    }

    for (auto const &authorities_inner : authorities) {
        for (std::optional<Address> const &authority : authorities_inner) {
            if (authority) {
                senders_and_authorities.insert(*authority);
            }
        }
    }

    return senders_and_authorities;
}

KINET_NAMESPACE_END
