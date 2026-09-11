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

add_library(kinet-vm-fuzzing OBJECT)

target_sources(kinet-vm-fuzzing PRIVATE
  "choice.hpp"
  "instruction_data.cpp"
  "instruction_data.hpp"
)

kinet_compile_options(kinet-vm-fuzzing)

target_include_directories(kinet-vm-fuzzing
  PUBLIC src/
)

target_link_libraries(kinet-vm-fuzzing
  PUBLIC kinet-vm::kinet-vm-compiler
  PUBLIC kinet-vm::kinet-vm-utils
)

add_library(kinet-vm::kinet-vm-fuzzing ALIAS kinet-vm-fuzzing)
