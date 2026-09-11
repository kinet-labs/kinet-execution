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

#include <category/core/runtime/non_temporal_memory.hpp>

#include <cstdlib>

namespace kinet::vm::test
{
    struct TestMemory
    {
        std::uint8_t *data;

        static constexpr std::uint32_t capacity = 4096;

        TestMemory()
            : data{reinterpret_cast<std::uint8_t *>(
                  std::aligned_alloc(32, capacity))}
        {
            KINET_ASSERT(data != nullptr);
            static_assert((capacity & 31) == 0);
            runtime::non_temporal_bzero(data, capacity);
        }

        TestMemory(TestMemory const &) = delete;
        TestMemory(TestMemory &&) = delete;
        TestMemory &operator=(TestMemory const &) = delete;
        TestMemory &operator=(TestMemory &&) = delete;

        ~TestMemory()
        {
            std::free(data);
        }
    };
}
