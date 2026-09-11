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

#include <category/core/bytes.hpp>

#include <optional>
#include <string>

namespace kinet::vm::utils
{
#ifdef KINET_COMPILER_TESTING
    extern bool is_fuzzing_kinet_vm;
#else
    static constexpr bool is_fuzzing_kinet_vm = false;
#endif

#ifdef KINET_COMPILER_STATS
    static constexpr bool collect_kinet_compiler_stats = true;
#else
    static constexpr bool collect_kinet_compiler_stats = false;
#endif

#ifdef KINET_COMPILER_HOT_PATH_STATS
    static constexpr bool collect_kinet_compiler_hot_path_stats = true;
#else
    static constexpr bool collect_kinet_compiler_hot_path_stats = false;
#endif

#ifdef KINET_COMPILER_TESTING
    extern bool is_compiler_runtime_debug_trace_enabled;
#else
    static constexpr bool is_compiler_runtime_debug_trace_enabled = false;
#endif

#ifdef KINET_COMPILER_TESTING
    std::optional<std::string>
    make_compiler_asm_log_path(bytes32_t const &base_name);
#else
    [[gnu::always_inline]] constexpr std::optional<std::string>
    make_compiler_asm_log_path(bytes32_t const &)
    {
        return std::nullopt;
    }
#endif
}
