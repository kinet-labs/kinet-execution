# Copyright (C) 2025 Category Labs, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Subcomponents

add_subdirectory(compiler)
add_subdirectory(evm)
add_subdirectory(fuzzing)
add_subdirectory(interpreter)
add_subdirectory(runtime)
add_subdirectory(utils)

# Main VM library (execution's entry point)

add_library(kinet-vm OBJECT)

target_sources(kinet-vm PRIVATE
    "code.hpp"
    "compiler.cpp"
    "compiler.hpp"
    "memory_pool.cpp"
    "memory_pool.hpp"
    "varcode_cache.cpp"
    "varcode_cache.hpp"
    "vm.cpp"
    "vm.hpp"
)

kinet_compile_options(kinet-vm)

target_include_directories(kinet-vm
    PUBLIC ${CATEGORY_MAIN_DIR}
)

target_link_libraries(kinet-vm
    PUBLIC TBB::tbb
    PUBLIC evmc::evmc
    PUBLIC asmjit::asmjit
    PUBLIC quill::quill
    PUBLIC kinet-vm::kinet-vm-compiler
    PUBLIC kinet-vm::kinet-vm-interpreter
    PRIVATE kinet-vm::kinet-vm-runtime
    PRIVATE kinet-vm::kinet-vm-utils
)

add_library(kinet-vm::kinet-vm ALIAS kinet-vm)

