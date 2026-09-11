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

include(ExternalProject)

ExternalProject_Add(
  ExecutionSpecTestFixtures
  URL "https://github.com/ethereum/execution-spec-tests/releases/download/v5.4.0/fixtures_develop.tar.gz"
  URL_HASH "SHA256=3e2b02d49fe903eda4fd8caca5cbf0d139c470e97e1de9a85299b1b034f97099"
  PREFIX ${CMAKE_BINARY_DIR}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON)

ExternalProject_Add(
  KinetSpecTestFixtures
  URL "https://github.com/kinet-labs/execution-specs/releases/download/tests-kinet@v1.2.1/fixtures_kinet.tar.gz"
  URL_HASH "SHA256=d42c558cb16ba64ed1f39ebeff3ec1f316c5eb6ef5589bd3f10f1a3251f4b43e"
  PREFIX ${CMAKE_BINARY_DIR}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON)

add_executable(kinet-ethereum-test)
target_link_libraries(kinet-ethereum-test PRIVATE GTest::gtest kinet-test-utils)
target_sources(
  kinet-ethereum-test
  PRIVATE include/blockchain_test.hpp
          include/event.hpp
          include/revision_map.hpp
          include/transaction_test.hpp
          src/blockchain_test.cpp
          src/event.cpp
          src/main.cpp
          src/transaction_test.cpp)

target_include_directories(
  kinet-ethereum-test PUBLIC ${CATEGORY_MAIN_DIR})
target_include_directories(
  kinet-ethereum-test PUBLIC ${PROJECT_SOURCE_DIR}/test/ethereum_test/include)
target_include_directories(
  kinet-ethereum-test PUBLIC ${PROJECT_SOURCE_DIR}/test/unit/common/include)
target_include_directories(kinet-ethereum-test
                           PRIVATE "${TOP_CURRENT_BINARY_DIR}/test")
kinet_compile_options(kinet-ethereum-test)

target_link_libraries(kinet-ethereum-test PRIVATE kinet_unit_test_common)

function(add_ethereum_test)
  set(ONE_VALUE_ARGS FORK)
  cmake_parse_arguments(ADD_ETHEREUM_TEST "" "${ONE_VALUE_ARGS}" "" ${ARGN})

  set(EXCLUSION_FILE
      "${CMAKE_CURRENT_SOURCE_DIR}/exclude/${ADD_ETHEREUM_TEST_FORK}.cmake")
  include(${EXCLUSION_FILE})
  set(TESTS_EXCLUDED "${ADD_ETHEREUM_TEST_FORK}_excluded_tests")

  list(JOIN ${TESTS_EXCLUDED} ":" TESTS_EXCLUDED)
  set(FILTER "-:${TESTS_EXCLUDED}")

  add_test(NAME ${ADD_ETHEREUM_TEST_FORK}_kinet_ethereum_test
           COMMAND kinet-ethereum-test --fork ${ADD_ETHEREUM_TEST_FORK}
                   --record-exec-events --gtest_filter=${FILTER})
endfunction()

function(add_kinet_test)
  set(ONE_VALUE_ARGS FORK)
  cmake_parse_arguments(ADD_KINET_TEST "" "${ONE_VALUE_ARGS}" "" ${ARGN})

  set(EXCLUSION_FILE
      "${CMAKE_CURRENT_SOURCE_DIR}/exclude/${ADD_KINET_TEST_FORK}.cmake")
  include(${EXCLUSION_FILE})
  set(TESTS_EXCLUDED "${ADD_KINET_TEST_FORK}_excluded_tests")

  list(JOIN ${TESTS_EXCLUDED} ":" TESTS_EXCLUDED)
  set(FILTER "-:${TESTS_EXCLUDED}")

  add_test(NAME ${ADD_KINET_TEST_FORK}_kinet_ethereum_test
           COMMAND kinet-ethereum-test --fork ${ADD_KINET_TEST_FORK}
                  # TODO: not ready yet
                  #  --record-exec-events
                   --blockchain-tests ${CMAKE_BINARY_DIR}/src/KinetSpecTestFixtures/blockchain_tests
                   --gtest_filter=${FILTER})
endfunction()

add_kinet_test(FORK KINET_EIGHT)
add_kinet_test(FORK KINET_NINE)
add_kinet_test(FORK KINET_TEN)

# KINET_NEXT Amsterdam spec tests, from a separate fixtures release. While the
# whole suite is excluded (see the exclusion file), the runner exits non-zero
# via its "No tests were run" guard, so the job is marked WILL_FAIL to keep
# ctest green. WILL_FAIL is set only while the suite is fully excluded: once
# individual tests are re-enabled by dropping entries from the exclusion list,
# the job runs normally so real failures (and unexpected passes) surface.
include(${CMAKE_CURRENT_SOURCE_DIR}/exclude/KINET_NEXT_amsterdam.cmake)
list(JOIN KINET_NEXT_amsterdam_excluded_tests ":" TESTS_EXCLUDED)
add_test(NAME KINET_NEXT_amsterdam_kinet_ethereum_test
         COMMAND kinet-ethereum-test --fork KINET_NEXT
                 --blockchain-tests ${CMAKE_BINARY_DIR}/src/KinetAmsterdamSpecTestFixtures/blockchain_tests
                 --blockchain-tests ${CMAKE_BINARY_DIR}/src/KinetEip7981SpecTestFixtures/blockchain_tests
                 --gtest_filter=-:${TESTS_EXCLUDED})
if(KINET_NEXT_amsterdam_excluded_tests STREQUAL "BlockchainTests.*")
  set_tests_properties(KINET_NEXT_amsterdam_kinet_ethereum_test
                       PROPERTIES WILL_FAIL TRUE)
endif()

add_ethereum_test(FORK berlin)
add_ethereum_test(FORK london)
add_ethereum_test(FORK paris)
add_ethereum_test(FORK shanghai)
add_ethereum_test(FORK cancun)
add_ethereum_test(FORK prague)
add_ethereum_test(FORK osaka)
