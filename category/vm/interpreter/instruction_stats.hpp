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

#pragma once

#include <cstdint>

namespace kinet::vm::interpreter::stats
{
#ifdef KINET_VM_INTERPRETER_STATS
    void begin(uint8_t const opcode);
    void end();
#else
    [[gnu::always_inline]] inline void begin(uint8_t const) {}

    [[gnu::always_inline]] inline void end() {}
#endif
}
