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

#pragma once

#include <evmc/evmc.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum kinet_status_code : int
{
    KINET_STATUS_SUCCESS = 0,
    KINET_STATUS_FAILURE = 1,
    KINET_STATUS_REVERT = 2,
    KINET_STATUS_OUT_OF_GAS = 3,
    KINET_STATUS_INVALID_INSTRUCTION = 4,
    KINET_STATUS_UNDEFINED_INSTRUCTION = 5,
    KINET_STATUS_STACK_OVERFLOW = 6,
    KINET_STATUS_STACK_UNDERFLOW = 7,
    KINET_STATUS_BAD_JUMP_DESTINATION = 8,
    KINET_STATUS_INVALID_MEMORY_ACCESS = 9,
    KINET_STATUS_CALL_DEPTH_EXCEEDED = 10,
    KINET_STATUS_STATIC_MODE_VIOLATION = 11,
    KINET_STATUS_PRECOMPILE_FAILURE = 12,
    KINET_STATUS_CONTRACT_VALIDATION_FAILURE = 13,
    KINET_STATUS_ARGUMENT_OUT_OF_RANGE = 14,
    KINET_STATUS_WASM_UNREACHABLE_INSTRUCTION = 15,
    KINET_STATUS_WASM_TRAP = 16,
    KINET_STATUS_INSUFFICIENT_BALANCE = 17,
    // Fork-only: no upstream evmc counterpart.
    KINET_STATUS_RESERVE_BALANCE_VIOLATION = 18,

    KINET_STATUS_INTERNAL_ERROR = -1,
    KINET_STATUS_REJECTED = -2,
    KINET_STATUS_OUT_OF_MEMORY = -3
};

enum evmc_status_code to_evmc_status_code(enum kinet_status_code code);
enum kinet_status_code from_evmc_status_code(enum evmc_status_code code);

#ifdef __cplusplus
} // extern "C"
#endif
