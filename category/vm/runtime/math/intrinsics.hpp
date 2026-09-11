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

// Platform-specific `mul` for the runtime math interface. The host build
// links the hand-rolled x86 assembly via the extern declarations below.

#pragma once

#include <category/core/runtime/uint256.hpp>

// It is assumed that if the `result` pointer overlaps with `left` and/or
// `right`, then `result` pointer is equal to `left` and/or `right`.
extern "C" void kinet_vm_runtime_mul(
    kinet::uint256_t *result, kinet::uint256_t const *left,
    kinet::uint256_t const *right) noexcept;

// It is assumed that if the `result` pointer overlaps with `left` and/or
// `right`, then `result` pointer is equal to `left` and/or `right`.
extern "C" void kinet_vm_runtime_mul_192(
    kinet::uint256_t *result, kinet::uint256_t const *left,
    kinet::uint256_t const *right) noexcept;

namespace kinet::vm::runtime
{
    constexpr void (*mul)(
        uint256_t *, uint256_t const *,
        uint256_t const *) noexcept = kinet_vm_runtime_mul;
}
