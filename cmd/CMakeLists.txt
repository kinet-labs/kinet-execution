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

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(CLI11 REQUIRED)

add_executable(
  kinet
  kinet/main.cpp
  kinet/event.cpp
  kinet/event.hpp)

kinet_compile_options(kinet)

target_link_libraries(kinet PRIVATE kinet_execution CLI11::CLI11)

add_executable(kinet-cli kinet_cli.cpp)
kinet_compile_options(kinet-cli)
target_link_libraries(kinet-cli PUBLIC kinet_execution CLI11::CLI11)

target_compile_definitions(kinet PRIVATE GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")
target_compile_definitions(kinet-cli
                           PRIVATE GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

add_subdirectory(vm/parser)

if(KINET_COMPILER_BENCHMARKS)
    add_subdirectory(vm/mce)
endif()
