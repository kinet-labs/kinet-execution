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

#include <category/execution/ethereum/reserve_balance.hpp>
#include <category/vm/evm/explicit_traits.hpp>
#include <category/vm/evm/traits.hpp>

KINET_NAMESPACE_BEGIN

template <Traits traits>
bool revert_transaction(
    Address const &, Transaction const &, uint256_t const &, uint64_t const,
    State &, trace::StateTracer &, ChainContext<traits> const &)
{
    return false;
}

EXPLICIT_EVM_TRAITS(revert_transaction);

template <Traits traits>
bool revert_transaction_cached(State &)
{
    return false;
}

EXPLICIT_EVM_TRAITS(revert_transaction_cached);

KINET_NAMESPACE_END
