# Copyright (C) 2025 Kinet Labs, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Apache-2.0 license as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Apache-2.0 license for more details.
#
# You should have received a copy of the Apache-2.0 license
# along with this program.  If not, see <http://www.apache.org/licenses/>.

enable_language(C)

add_library(kinet-vm-utils OBJECT)

target_sources(kinet-vm-utils PRIVATE
    "debug.cpp"
    "debug.hpp"
    "load_program.hpp"
    "lru_weight_cache.hpp"
    "rc_ptr.hpp"
    "parser.cpp"
    "parser.hpp"
    "scope_exit.hpp"
    "traits.hpp"

    # evm-as
    "evm-as.hpp"
    "evm-as/builder.hpp"
    "evm-as/compiler.cpp"
    "evm-as/compiler.hpp"
    "evm-as/instruction.hpp"
    "evm-as/kernel-builder.hpp"
    "evm-as/resolver.hpp"
    "evm-as/sugar.hpp"
    "evm-as/validator.hpp"
    "evm-as/utils.hpp"
)

kinet_compile_options(kinet-vm-utils)

target_include_directories(kinet-vm-utils
    PUBLIC ${CATEGORY_MAIN_DIR}
)

target_link_libraries(kinet-vm-utils
    PUBLIC kinet-vm::kinet-vm-runtime
    PRIVATE kinet-vm::kinet-vm-evm
)

add_library(kinet-vm::kinet-vm-utils ALIAS kinet-vm-utils)
