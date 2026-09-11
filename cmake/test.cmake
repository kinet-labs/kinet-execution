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

include(CTest)

find_package(GTest REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gmock REQUIRED IMPORTED_TARGET gmock)

include(GoogleTest)

function(add_unit_test)
  set(ONE_VALUE_ARGS TARGET)
  set(MULTI_VALUE_ARGS SOURCES LIBRARIES)
  cmake_parse_arguments(ADD_UNIT_TEST "" "${ONE_VALUE_ARGS}"
                        "${MULTI_VALUE_ARGS}" ${ARGN})

  add_executable(
    ${ADD_UNIT_TEST_TARGET}
    ${ADD_UNIT_TEST_SOURCES}
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../test/unit/common/src/test/main.cpp)
  kinet_compile_options(${ADD_UNIT_TEST_TARGET})

  target_link_libraries(
    ${ADD_UNIT_TEST_TARGET}
    PUBLIC GTest::gtest GTest::gmock kinet_unit_test_common
           ${ADD_UNIT_TEST_LIBRARIES})
  gtest_discover_tests(${ADD_UNIT_TEST_TARGET})
endfunction()

function(add_integration_test)
  set(ONE_VALUE_ARGS TARGET)
  cmake_parse_arguments(ADD_INT_TEST "" "${ONE_VALUE_ARGS}" "" ${ARGN})

  add_unit_test(${ADD_INT_TEST_TARGET} ${ARGN})
  target_link_libraries(${ADD_INT_TEST_TARGET} PUBLIC kinet_execution)

  if(NOT TARGET integration_tests)
    add_custom_target(integration_tests)
  endif()
  add_dependencies(integration_tests ${ADD_INT_TEST_TARGET})
endfunction()
