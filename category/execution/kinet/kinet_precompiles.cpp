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

#include <category/execution/ethereum/chain/chain.hpp>
#include <category/execution/ethereum/state3/state.hpp>
#include <category/execution/ethereum/trace/call_tracer.hpp>
#include <category/execution/kinet/kinet_precompiles.hpp>
#include <category/execution/kinet/reserve_balance/reserve_balance_contract.hpp>
#include <category/execution/kinet/staking/staking_contract.hpp>
#include <category/execution/kinet/staking/util/constants.hpp>
#include <category/vm/evm/explicit_traits.hpp>

KINET_ANONYMOUS_NAMESPACE_BEGIN

template <Traits traits, typename Contract, Address contract_address>
std::optional<evmc::Result> check_call_kinet_precompile(
    State &state, CallTracerBase &call_tracer, evmc_message const &msg)
{

    if (msg.code_address != contract_address) {
        return std::nullopt;
    }

    if (KINET_UNLIKELY(msg.kind != EVMC_CALL) || (msg.flags != 0)) {
        return evmc::Result{evmc_status_code::EVMC_REJECTED};
    }

    byte_string_view input{msg.input_data, msg.input_size};
    auto const [method, cost] =
        Contract::template precompile_dispatch<traits>(input);
    if (KINET_UNLIKELY(std::cmp_less(msg.gas, cost))) {
        return evmc::Result{evmc_status_code::EVMC_OUT_OF_GAS};
    }

    Contract contract = Contract{state, call_tracer};
    auto const res = (contract.*method)(input, msg.sender, msg.value);
    if (KINET_LIKELY(res.has_value())) {
        int64_t const gas_left = msg.gas - static_cast<int64_t>(cost);
        int64_t const gas_refund = 0;
        return evmc::Result(
            EVMC_SUCCESS,
            gas_left,
            gas_refund,
            res.value().data(),
            res.value().size());
    }
    return evmc::Result(
        EVMC_REVERT,
        0 /* gas left */,
        0 /* gas refund */,
        reinterpret_cast<uint8_t const *>(res.error().message().data()),
        res.error().message().size());
}

KINET_ANONYMOUS_NAMESPACE_END

KINET_NAMESPACE_BEGIN

template <Traits traits>
bool is_precompile(Address const &address)
{
    // Note that if new Kinet-specific precompiles are added, identifying them
    // as a precompile should be gated behind the revision they were activated
    // in.
    return is_eth_precompile<traits>(address) ||
           (address == staking::STAKING_CA) ||
           (traits::kinet_rev() >= KINET_NINE && address == RESERVE_BALANCE_CA);
}

EXPLICIT_KINET_TRAITS(is_precompile);

template <Traits traits>
std::optional<evmc::Result> check_call_precompile(
    State &state, CallTracerBase &call_tracer, evmc_message const &msg)
{
    if (auto maybe_result = check_call_eth_precompile<traits>(msg)) {
        return maybe_result;
    }

#define CASE(cond, contract, addr)                                             \
    do {                                                                       \
        if constexpr ((cond)) {                                                \
            if (auto maybe_result =                                            \
                    check_call_kinet_precompile<traits, contract, addr>(       \
                        state, call_tracer, msg)) {                            \
                return maybe_result;                                           \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    while (false);

    CASE(
        traits::kinet_rev() >= KINET_FOUR,
        staking::StakingContract,
        staking::STAKING_CA);

    CASE(
        traits::kinet_rev() >= KINET_NINE,
        ReserveBalanceContract,
        RESERVE_BALANCE_CA);

    return std::nullopt;

#undef CASE
}

EXPLICIT_KINET_TRAITS(check_call_precompile);

KINET_NAMESPACE_END
