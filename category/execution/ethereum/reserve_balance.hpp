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

#pragma once

#include <category/core/address.hpp>
#include <category/core/config.hpp>
#include <category/core/int.hpp>
#include <category/execution/ethereum/chain/chain.hpp>
#include <category/execution/ethereum/trace/state_tracer.hpp>
#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.h>

#include <cstdint>
#include <optional>

KINET_NAMESPACE_BEGIN

class State;
struct Transaction;

template <Traits traits>
bool revert_transaction(
    Address const &sender, Transaction const &,
    uint256_t const &base_fee_per_gas, uint64_t i, State &,
    trace::StateTracer &state_tracer, ChainContext<traits> const &);

template <Traits traits>
bool revert_transaction_cached(State &);

template <Traits traits>
    requires is_kinet_trait_v<traits>
void init_reserve_balance_context(
    State &state, Address const &sender, Transaction const &tx,
    std::optional<uint256_t> const &base_fee_per_gas, uint64_t i,
    trace::StateTracer &state_tracer, ChainContext<traits> const &ctx);

KINET_NAMESPACE_END
