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

add_library(kinet-vm-test-utils OBJECT)

target_sources(kinet-vm-test-utils PRIVATE
    "evm-as_utils.hpp"
    "test_context.hpp"
    "test_host.hpp"
    "test_memory.hpp"
)

kinet_compile_options(kinet-vm-test-utils)

target_link_libraries(kinet-vm-test-utils
    PUBLIC TBB::tbb
    PUBLIC intx::intx
    PUBLIC evmc::evmc
    PUBLIC asmjit::asmjit
    PUBLIC quill::quill
    PUBLIC kinet-vm::kinet-vm-compiler
    PUBLIC kinet-vm::kinet-vm-interpreter
    PUBLIC kinet-vm::kinet-vm-runtime
    PUBLIC kinet-vm::kinet-vm-utils
    PUBLIC kinet_execution
)

add_library(kinet-vm::kinet-vm-test-utils ALIAS kinet-vm-test-utils)
