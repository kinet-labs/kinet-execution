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

#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/vm/code.hpp>
#include <category/vm/evm/traits.hpp>

#include <variant>

KINET_NAMESPACE_BEGIN

class State;

namespace trace
{
    using StateTracer = std::monostate;

    [[gnu::always_inline]] inline bool is_code_tracer(StateTracer const &)
    {
        return false;
    }

    [[gnu::always_inline]] inline void
    on_read_code(StateTracer &, bytes32_t const &, vm::SharedIntercode const &)
    {
    }

    [[gnu::always_inline]] inline void on_frame_reject(StateTracer &, State &)
    {
    }

    [[gnu::always_inline]] inline void reset(StateTracer &) {}

    template <Traits>
    [[gnu::always_inline]] inline void run_tracer(StateTracer &, State &)
    {
    }
}

KINET_NAMESPACE_END
