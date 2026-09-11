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

#include <category/vm/evm/traits.hpp>
#include <category/vm/runtime/types.hpp>

namespace kinet::vm::runtime
{
    template <Traits traits>
    void create(
        Context *ctx, uint256_t *result_ptr, uint256_t const *value_ptr,
        uint256_t const *offset_ptr, uint256_t const *size_ptr,
        int64_t remaining_block_base_gas);

    template <Traits traits>
    void create2(
        Context *ctx, uint256_t *result_ptr, uint256_t const *value_ptr,
        uint256_t const *offset_ptr, uint256_t const *size_ptr,
        uint256_t const *salt_ptr, int64_t remaining_block_base_gas);
}
