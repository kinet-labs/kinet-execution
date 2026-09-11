# Copyright (C) 2025-26 Category Labs, Inc.
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

cmake_minimum_required(VERSION 3.20)

project(triedb-driver)

# triedb_driver

if (NOT DEFINED KINET_EXECUTION_DIR)
  message(FATAL_ERROR "KINET_EXECUTION_DIR must be passed in by build.rs")
endif()

# This is the library already built by kinet-cxx, so that we don't built it
# again
add_library(kinet_execution_local SHARED IMPORTED)
set_target_properties(kinet_execution_local PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/../../../"
  IMPORTED_LOCATION "${KINET_EXECUTION_DIR}/libkinet_execution.so"
)

add_subdirectory("../../../" "kinet-execution-build"
)# needed for kinet-trie

add_library(triedb_driver SHARED "${PROJECT_SOURCE_DIR}/include/ffi.h"
                                 "${PROJECT_SOURCE_DIR}/src/ffi.cpp")

target_include_directories(triedb_driver PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Interface link kinet_execution so that we'll take any configuration we need,
# but we won't build it
target_link_libraries(triedb_driver INTERFACE kinet_execution)
target_link_libraries(triedb_driver PUBLIC kinet_execution_local)
target_link_libraries(triedb_driver PUBLIC asmjit::asmjit evmc intx 
                      nlohmann_json::nlohmann_json quill unordered_dense ankerl_hash)

kinet_compile_options(triedb_driver)
target_compile_definitions(triedb_driver PRIVATE KINET_CXX_CTYPES_USE_EVMC_HPP=1)
