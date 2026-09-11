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

# benchmark calc_min_version
add_executable(calc_min_version_bench "calc_min_version_bench.cpp")
kinet_compile_options(calc_min_version_bench)
target_link_libraries(calc_min_version_bench PUBLIC kinet_trie kinet_async kinet_core)

# benchmark async reads
add_executable(async_read_bench "async_read_bench.cpp")
kinet_compile_options(async_read_bench)
target_link_libraries(
  async_read_bench PUBLIC kinet_trie kinet_async kinet_core
                                  CLI11::CLI11 quill::quill)
