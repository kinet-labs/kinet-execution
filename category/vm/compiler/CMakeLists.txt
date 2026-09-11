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
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

add_library(kinet-vm-compiler OBJECT)

target_sources(kinet-vm-compiler PRIVATE
    "transactional_unordered_map.hpp"
    "types.hpp"
    # IR
    "ir/basic_blocks.cpp"
    "ir/basic_blocks.hpp"
    "ir/instruction.hpp"
    # x86 backend
    "ir/x86.hpp"
    "ir/x86.cpp"
    "ir/x86/emitter.cpp"
    "ir/x86/emitter.hpp"
    "ir/x86/types.hpp"
    "ir/x86/virtual_stack.cpp"
    "ir/x86/virtual_stack.hpp"
)

kinet_compile_options(kinet-vm-compiler)

target_include_directories(kinet-vm-compiler
    PUBLIC ${CATEGORY_MAIN_DIR}
)

target_link_libraries(kinet-vm-compiler
    PUBLIC asmjit::asmjit
    PUBLIC evmc::evmc
    PUBLIC kinet-vm::kinet-vm-evm
    PUBLIC kinet-vm::kinet-vm-runtime
    PUBLIC kinet-vm::kinet-vm-utils
    PUBLIC quill::quill
)

add_library(kinet-vm::kinet-vm-compiler ALIAS kinet-vm-compiler)
