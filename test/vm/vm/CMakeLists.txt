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

# Testing VM

add_library(blockchain-test-vm STATIC)

target_sources(blockchain-test-vm
    PRIVATE
        test_vm.hpp
        test_vm.cpp
)

target_link_libraries(blockchain-test-vm
    PUBLIC
        evmc::evmc
        kinet-vm::kinet-vm
        kinet-vm::kinet-vm-compiler
        kinet-vm::kinet-vm-interpreter
)

target_include_directories(blockchain-test-vm
    PUBLIC .
)
kinet_compile_options(blockchain-test-vm)
