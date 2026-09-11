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
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#pragma once

#include <category/core/runtime/uint256/portable.hpp>
#include <category/core/runtime/uint256/types.hpp>

#include <cstdint>

// zkVM (RISC-V) replacement for the AVX2/BMI2 x86 intrinsics. RISC-V has no
// specialised instructions (mulx, shld, shrd, div, addc/subb) corresponding
// to the x86 backend, so we re-export the portable implementations as the
// intrinsics implementations.

namespace kinet::uint256::intrinsics
{
    using portable::addc;
    using portable::div;
    using portable::mulx;
    using portable::shld;
    using portable::shrd;
    using portable::subb;
    using portable::truncating_mul;

    [[gnu::always_inline]] constexpr uint64_t
    force(uint64_t const expr) noexcept
    {
        return expr;
    }
}
