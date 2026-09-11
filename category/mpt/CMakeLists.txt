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

include(CheckCXXSourceRuns)

project(kinet_trie)
enable_testing()

option(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# ##############################################################################
# deps
# ##############################################################################

find_package(Boost 1.83 # 1.83 really is the minimum
             CONFIG REQUIRED COMPONENTS context json thread)
find_package(GTest)

pkg_check_modules(archive REQUIRED IMPORTED_TARGET libarchive)

# ##############################################################################
# libs
# ##############################################################################

add_library(
  kinet_trie
  OBJECT
  "compute.cpp"
  "compute.hpp"
  "config.hpp"
  "copy_trie.cpp"
  "db.cpp"
  "db.hpp"
  "db_error.hpp"
  "db_metadata_context.cpp"
  "db_metadata_context.hpp"
  "find.cpp"
  "find_notify_fiber.cpp"
  "find_request_sender.hpp"
  "nibbles_view.hpp"
  "nibbles_view_fmt.hpp"
  "node.cpp"
  "node.hpp"
  "node_cache.hpp"
  "node_cursor.hpp"
  "ondisk_db_config.hpp"
  "request.hpp"
  "read_node_blocking.cpp"
  "state_machine.hpp"
  "state_machine_kind.cpp"
  "state_machine_kind.hpp"
  "traverse.hpp"
  "traverse_util.hpp"
  "trie.cpp"
  "trie.hpp"
  "update.hpp"
  "update_aux.cpp"
  "util.hpp")
target_include_directories(kinet_trie PUBLIC ${CATEGORY_MAIN_DIR})
target_include_directories(kinet_trie PRIVATE "third_party")
kinet_compile_options(kinet_trie)
target_link_libraries(kinet_trie PRIVATE Boost::boost)
target_link_libraries(kinet_trie PUBLIC concurrentqueue)
target_link_libraries(kinet_trie PUBLIC kinet_async)
target_link_libraries(kinet_trie PUBLIC quill::quill) # TODO: remove
add_executable(kinet-mpt "cli_tool_main.cpp" "cli_tool_impl.cpp")
kinet_compile_options(kinet-mpt)
target_link_libraries(kinet-mpt PUBLIC kinet_execution PkgConfig::zstd
                                       PkgConfig::archive CLI11::CLI11)

target_compile_definitions(kinet-mpt
                           PRIVATE GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

function(add_trie_test)
  set(ONE_VALUE_ARGS TARGET TEST_FILTER)
  set(MULTI_VALUE_ARGS SOURCES LINK_LIBRARIES)
  cmake_parse_arguments(ADD_TRIE_TEST "" "${ONE_VALUE_ARGS}"
                        "${MULTI_VALUE_ARGS}" ${ARGN})

  add_executable(${ADD_TRIE_TEST_TARGET} ${ADD_TRIE_TEST_SOURCES})
  kinet_compile_options(${ADD_TRIE_TEST_TARGET})
  target_link_libraries(
    ${ADD_TRIE_TEST_TARGET}
    PUBLIC kinet_execution GTest::GTest kinet_gtest_main
           kinet_unit_test_common ${ADD_TRIE_TEST_LINK_LIBRARIES})
  gtest_discover_tests(
    ${ADD_TRIE_TEST_TARGET}
    TEST_PREFIX ${PROJECT_NAME}/ TEST_FILTER ${ADD_TRIE_TEST_TEST_FILTER}
    PROPERTIES ENVIRONMENT ASAN_OPTIONS=abort_on_error=1 ENVIRONMENT
               UBSAN_OPTIONS=halt_on_error=1,print_stacktrace=1 ENVIRONMENT
               TSAN_OPTIONS=external_symbolizer_path=/usr/bin/llvm-symbolizer)
endfunction()

add_subdirectory("test")
add_subdirectory("bench")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_subdirectory("test/fuzz")
endif()
