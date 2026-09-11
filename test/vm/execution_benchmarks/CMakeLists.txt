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

add_executable(execution-benchmarks)
target_sources(execution-benchmarks
    PRIVATE
        benchmarks.cpp
        benchmarktest.hpp
        benchmarktest_loader.cpp
)
target_include_directories(execution-benchmarks
    PRIVATE "${TOP_CURRENT_BINARY_DIR}/test"
    PRIVATE "${TEST_DATA_DIR}/unit/common/include"
    PRIVATE "${CATEGORY_MAIN_DIR}"
)
kinet_compile_options(execution-benchmarks)

target_link_libraries(execution-benchmarks
    PRIVATE benchmark::benchmark
    PRIVATE blockchain-test-vm
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE kinet-test-utils
    PRIVATE kinet-vm::kinet-vm-test-utils
)
