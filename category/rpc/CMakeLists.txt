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

cmake_minimum_required(VERSION 3.27)

cmake_policy(SET CMP0144 NEW) # find_package uses upper-case _ROOT variables

project(kinet_rpc)

add_library(
  kinet_rpc
  OBJECT
  # rpc
  "chain_context_buffer.cpp"
  "chain_context_buffer.hpp"
  "eth_simulate_block_hash_buffer.cpp"
  "eth_simulate_block_hash_buffer.hpp"
  "lazy_block_hash.cpp" 
  "lazy_block_hash.hpp"
  "kinet_executor.cpp"
  "kinet_executor.h"
  "overrides.cpp" 
  "overrides.h" 
  "overrides.hpp"
  )

target_include_directories(kinet_rpc PUBLIC ${CATEGORY_MAIN_DIR})

kinet_compile_options(kinet_rpc)
target_link_libraries(kinet_rpc PRIVATE kinet_execution_native)

kinet_add_test_folder(".")
