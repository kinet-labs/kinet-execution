// Copyright (C) 2025-26 Kinet Labs, Inc.
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

#include <category/core/assert.h>
#include <category/vm/evm/status_code.h>

#include <evmc/evmc.h>

#include <utility>

#define KINET_ASSERT_STATUS_EQ(name)                                           \
    static_assert(                                                             \
        std::to_underlying(KINET_STATUS_##name) ==                             \
        std::to_underlying(EVMC_##name))

KINET_ASSERT_STATUS_EQ(SUCCESS);
KINET_ASSERT_STATUS_EQ(FAILURE);
KINET_ASSERT_STATUS_EQ(REVERT);
KINET_ASSERT_STATUS_EQ(OUT_OF_GAS);
KINET_ASSERT_STATUS_EQ(INVALID_INSTRUCTION);
KINET_ASSERT_STATUS_EQ(UNDEFINED_INSTRUCTION);
KINET_ASSERT_STATUS_EQ(STACK_OVERFLOW);
KINET_ASSERT_STATUS_EQ(STACK_UNDERFLOW);
KINET_ASSERT_STATUS_EQ(BAD_JUMP_DESTINATION);
KINET_ASSERT_STATUS_EQ(INVALID_MEMORY_ACCESS);
KINET_ASSERT_STATUS_EQ(CALL_DEPTH_EXCEEDED);
KINET_ASSERT_STATUS_EQ(STATIC_MODE_VIOLATION);
KINET_ASSERT_STATUS_EQ(PRECOMPILE_FAILURE);
KINET_ASSERT_STATUS_EQ(CONTRACT_VALIDATION_FAILURE);
KINET_ASSERT_STATUS_EQ(ARGUMENT_OUT_OF_RANGE);
KINET_ASSERT_STATUS_EQ(WASM_UNREACHABLE_INSTRUCTION);
KINET_ASSERT_STATUS_EQ(WASM_TRAP);
KINET_ASSERT_STATUS_EQ(INSUFFICIENT_BALANCE);
KINET_ASSERT_STATUS_EQ(INTERNAL_ERROR);
KINET_ASSERT_STATUS_EQ(REJECTED);
KINET_ASSERT_STATUS_EQ(OUT_OF_MEMORY);

#undef KINET_ASSERT_STATUS_EQ

static_assert(
    std::to_underlying(KINET_STATUS_RESERVE_BALANCE_VIOLATION) ==
    std::to_underlying(EVMC_KINET_RESERVE_BALANCE_VIOLATION));

evmc_status_code to_evmc_status_code(kinet_status_code const code)
{
    switch (code) {
    case KINET_STATUS_SUCCESS:
        return EVMC_SUCCESS;
    case KINET_STATUS_FAILURE:
        return EVMC_FAILURE;
    case KINET_STATUS_REVERT:
        return EVMC_REVERT;
    case KINET_STATUS_OUT_OF_GAS:
        return EVMC_OUT_OF_GAS;
    case KINET_STATUS_INVALID_INSTRUCTION:
        return EVMC_INVALID_INSTRUCTION;
    case KINET_STATUS_UNDEFINED_INSTRUCTION:
        return EVMC_UNDEFINED_INSTRUCTION;
    case KINET_STATUS_STACK_OVERFLOW:
        return EVMC_STACK_OVERFLOW;
    case KINET_STATUS_STACK_UNDERFLOW:
        return EVMC_STACK_UNDERFLOW;
    case KINET_STATUS_BAD_JUMP_DESTINATION:
        return EVMC_BAD_JUMP_DESTINATION;
    case KINET_STATUS_INVALID_MEMORY_ACCESS:
        return EVMC_INVALID_MEMORY_ACCESS;
    case KINET_STATUS_CALL_DEPTH_EXCEEDED:
        return EVMC_CALL_DEPTH_EXCEEDED;
    case KINET_STATUS_STATIC_MODE_VIOLATION:
        return EVMC_STATIC_MODE_VIOLATION;
    case KINET_STATUS_PRECOMPILE_FAILURE:
        return EVMC_PRECOMPILE_FAILURE;
    case KINET_STATUS_CONTRACT_VALIDATION_FAILURE:
        return EVMC_CONTRACT_VALIDATION_FAILURE;
    case KINET_STATUS_ARGUMENT_OUT_OF_RANGE:
        return EVMC_ARGUMENT_OUT_OF_RANGE;
    case KINET_STATUS_WASM_UNREACHABLE_INSTRUCTION:
        return EVMC_WASM_UNREACHABLE_INSTRUCTION;
    case KINET_STATUS_WASM_TRAP:
        return EVMC_WASM_TRAP;
    case KINET_STATUS_INSUFFICIENT_BALANCE:
        return EVMC_INSUFFICIENT_BALANCE;
    case KINET_STATUS_INTERNAL_ERROR:
        return EVMC_INTERNAL_ERROR;
    case KINET_STATUS_REJECTED:
        return EVMC_REJECTED;
    case KINET_STATUS_OUT_OF_MEMORY:
        return EVMC_OUT_OF_MEMORY;
    case KINET_STATUS_RESERVE_BALANCE_VIOLATION:
        return EVMC_KINET_RESERVE_BALANCE_VIOLATION;
    }
    KINET_ABORT("unhandled kinet_status_code");
}

kinet_status_code from_evmc_status_code(evmc_status_code const code)
{
    switch (code) {
    case EVMC_SUCCESS:
        return KINET_STATUS_SUCCESS;
    case EVMC_FAILURE:
        return KINET_STATUS_FAILURE;
    case EVMC_REVERT:
        return KINET_STATUS_REVERT;
    case EVMC_OUT_OF_GAS:
        return KINET_STATUS_OUT_OF_GAS;
    case EVMC_INVALID_INSTRUCTION:
        return KINET_STATUS_INVALID_INSTRUCTION;
    case EVMC_UNDEFINED_INSTRUCTION:
        return KINET_STATUS_UNDEFINED_INSTRUCTION;
    case EVMC_STACK_OVERFLOW:
        return KINET_STATUS_STACK_OVERFLOW;
    case EVMC_STACK_UNDERFLOW:
        return KINET_STATUS_STACK_UNDERFLOW;
    case EVMC_BAD_JUMP_DESTINATION:
        return KINET_STATUS_BAD_JUMP_DESTINATION;
    case EVMC_INVALID_MEMORY_ACCESS:
        return KINET_STATUS_INVALID_MEMORY_ACCESS;
    case EVMC_CALL_DEPTH_EXCEEDED:
        return KINET_STATUS_CALL_DEPTH_EXCEEDED;
    case EVMC_STATIC_MODE_VIOLATION:
        return KINET_STATUS_STATIC_MODE_VIOLATION;
    case EVMC_PRECOMPILE_FAILURE:
        return KINET_STATUS_PRECOMPILE_FAILURE;
    case EVMC_CONTRACT_VALIDATION_FAILURE:
        return KINET_STATUS_CONTRACT_VALIDATION_FAILURE;
    case EVMC_ARGUMENT_OUT_OF_RANGE:
        return KINET_STATUS_ARGUMENT_OUT_OF_RANGE;
    case EVMC_WASM_UNREACHABLE_INSTRUCTION:
        return KINET_STATUS_WASM_UNREACHABLE_INSTRUCTION;
    case EVMC_WASM_TRAP:
        return KINET_STATUS_WASM_TRAP;
    case EVMC_INSUFFICIENT_BALANCE:
        return KINET_STATUS_INSUFFICIENT_BALANCE;
    case EVMC_KINET_RESERVE_BALANCE_VIOLATION:
        return KINET_STATUS_RESERVE_BALANCE_VIOLATION;
    case EVMC_INTERNAL_ERROR:
        return KINET_STATUS_INTERNAL_ERROR;
    case EVMC_REJECTED:
        return KINET_STATUS_REJECTED;
    case EVMC_OUT_OF_MEMORY:
        return KINET_STATUS_OUT_OF_MEMORY;
    }
    KINET_ABORT("unhandled evmc_status_code");
}
