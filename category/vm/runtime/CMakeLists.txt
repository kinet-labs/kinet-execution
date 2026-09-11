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

enable_language(ASM)

add_library(kinet-vm-runtime OBJECT)

target_sources(kinet-vm-runtime PRIVATE
    "allocator.hpp"
    "allocator.cpp"
    "cached_allocator.hpp"
    "bin.hpp"
    "call.hpp"
    "call.cpp"
    "context.S"
    "context.cpp"
    "create.hpp"
    "create.cpp"
    "data.hpp"
    "data.cpp"
    "detail.hpp"
    "environment.hpp"
    "environment.cpp"
    "exit.S"
    "exit.hpp"
    "exit.cpp"
    "keccak.hpp"
    "log.hpp"
    "log.cpp"
    "math.S"
    "math.hpp"
    "math/intrinsics.hpp"
    "memory.hpp"
    "runtime.hpp"
    "selfdestruct.hpp"
    "selfdestruct.cpp"
    "storage.cpp"
    "storage.hpp"
    "storage_costs.hpp"
    "transmute.S"
    "transmute.hpp"
    "transmute/intrinsics.hpp"
    "types.hpp"
)

kinet_compile_options(kinet-vm-runtime)

target_include_directories(kinet-vm-runtime
    PUBLIC ${CATEGORY_MAIN_DIR}
)

target_link_libraries(kinet-vm-runtime
    PUBLIC evmc::evmc
    PUBLIC kinet_core
    PUBLIC kinet-vm::kinet-vm-evm
)

add_library(kinet-vm::kinet-vm-runtime ALIAS kinet-vm-runtime)
