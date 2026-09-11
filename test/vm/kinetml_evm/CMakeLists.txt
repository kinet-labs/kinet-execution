# Copyright (C) 2025-26 Kinet Labs, Inc.
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

find_program(OPAM opam REQUIRED)

execute_process(
    COMMAND ${OPAM} exec -- which dune
    OUTPUT_VARIABLE DUNE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE DUNE_RESULT
)

if(NOT DUNE_RESULT EQUAL 0)
    message(FATAL_ERROR "unable to find dune install path via opam")
endif()

set(LIBKINETML_WORKING_DIR "${CMAKE_SOURCE_DIR}/third_party/kinet-execution-specs")
set(LIBKINETML_BUILD_DIR "${LIBKINETML_WORKING_DIR}/_build")
set(LIBKINETML_EVM "${LIBKINETML_BUILD_DIR}/default/bindings/vm/libkinetml_evm.so")

add_custom_target(build-kinetml-evm ALL
    COMMAND ${DUNE} build bindings/vm/libkinetml_evm.so --profile release
    WORKING_DIRECTORY "${LIBKINETML_WORKING_DIR}"
    BYPRODUCTS "${LIBKINETML_EVM}"
    COMMENT "Building OCaml VM reference implementation with ${DUNE}"
    VERBATIM
)

set_property(
    DIRECTORY
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
    "${LIBKINETML_BUILD_DIR}"
)

add_library(kinetml-evm SHARED IMPORTED GLOBAL)

set_target_properties(kinetml-evm PROPERTIES
  IMPORTED_LOCATION "${LIBKINETML_EVM}"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

add_dependencies(kinetml-evm build-kinetml-evm)
