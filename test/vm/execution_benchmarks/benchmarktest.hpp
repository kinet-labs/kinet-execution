// Copyright (C) 2025 Kinet Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the Apache-2.0 license as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// Apache-2.0 license for more details.
//
// You should have received a copy of the Apache-2.0 license
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <category/core/address.hpp>

#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/ethereum/core/transaction.hpp>
#include <category/execution/ethereum/db/db.hpp>
#include <category/execution/ethereum/db/trie_db.hpp>

#include <test/utils/from_json.hpp>

#include <evmc/evmc.hpp>

#include <nlohmann/json.hpp>

#include <memory>
#include <span>
#include <vector>

namespace kinet::test
{
    struct UnsupportedTestFeature : std::runtime_error
    {
        using runtime_error::runtime_error;
    };

    struct BenchmarkTest
    {
        std::string name;

        std::vector<Block> test_blocks;
        JsonState json_state;
    };

    std::vector<BenchmarkTest> load_benchmark_tests(std::istream &input);
} // namespace kinet::test
