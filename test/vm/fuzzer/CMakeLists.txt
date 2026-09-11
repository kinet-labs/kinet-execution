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

add_executable(kinet-compiler-fuzzer)

target_sources(kinet-compiler-fuzzer PRIVATE
  assertions.cpp
  assertions.hpp
  compiler_hook.hpp
  fuzzer.cpp
  generator.hpp)

target_link_libraries(kinet-compiler-fuzzer
  PRIVATE kinetml-evm
  PRIVATE blockchain-test-vm
  PRIVATE kinet-vm::kinet-vm-fuzzing
  PRIVATE kinet_execution
  PRIVATE kinet-test-utils
  PRIVATE kinet-vm-test-utils
  PRIVATE CLI11::CLI11
)
kinet_compile_options(kinet-compiler-fuzzer)
