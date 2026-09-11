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

#ifdef KINET_COMPILER_TESTING
    #include <category/core/assert.h>
    #include <category/core/bytes.hpp>
    #include <category/core/hex.hpp>

    #include <cstdlib>
    #include <cstring>
    #include <filesystem>
    #include <optional>
    #include <sstream>
    #include <string>

namespace kinet::vm::utils
{
    static bool env_flag_enabled(char const *const name)
    {
        char const *const value = std::getenv(name);
        return value && std::strcmp(value, "1") == 0;
    }

    bool is_fuzzing_kinet_vm = env_flag_enabled("KINET_COMPILER_FUZZING");

    bool is_compiler_runtime_debug_trace_enabled =
        env_flag_enabled("KINET_COMPILER_DEBUG_TRACE");

    std::optional<std::string>
    make_compiler_asm_log_path(bytes32_t const &base_name)
    {
        if (base_name == bytes32_t{}) {
            return std::nullopt;
        }
        static char const *debug_dir = std::getenv("KINET_COMPILER_ASM_DIR");
        if (debug_dir) {
            KINET_ASSERT(std::filesystem::is_directory(debug_dir));
            std::ostringstream file(std::ostringstream::ate);
            file.str(debug_dir);
            file << '/';
            file << to_hex(base_name);
            return file.str();
        }
        return std::nullopt;
    }
}
#endif
