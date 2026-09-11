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

include(GoogleTest)

if(KINET_COMPILER_TESTING)
    find_package(GTest REQUIRED)
endif()

if(KINET_COMPILER_BENCHMARKS)
    find_package(benchmark REQUIRED)
endif()

if(KINET_COMPILER_BENCHMARKS)
  add_subdirectory(compile_benchmarks)
  add_subdirectory(execution_benchmarks)
  add_subdirectory(micro_benchmarks)
endif()

if(KINET_COMPILER_TESTING)
  add_subdirectory(kinetml_evm)
  add_subdirectory(fuzzer)
endif()

if(KINET_COMPILER_BENCHMARKS OR KINET_COMPILER_TESTING)
  add_subdirectory(vm)
endif()

add_subdirectory(utils)
add_subdirectory(unit)
