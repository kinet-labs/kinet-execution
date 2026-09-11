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

#include <category/vm/evm/opcodes.hpp>
#include <category/vm/evm/traits.hpp>
#include <category/vm/interpreter/intercode.hpp>
#include <category/vm/runtime/types.hpp>

#include <evmc/evmc.h>

namespace kinet::vm::interpreter
{
    constexpr auto debug_enabled = false;

    // No-op trace under the bare-metal zkVM environment, where there is
    // no stderr to write to.
    [[gnu::always_inline]]
    inline void trace(
        [[maybe_unused]] Intercode const &analysis,
        [[maybe_unused]] int64_t const gas_remaining,
        [[maybe_unused]] uint8_t const *const instr_ptr)
    {
    }
}
