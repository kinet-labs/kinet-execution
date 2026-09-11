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
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#include "benchmarktest.hpp"

#include <category/core/runtime/uint256.hpp>
#include <category/execution/ethereum/core/rlp/block_rlp.hpp>
#include <category/vm/evm/switch_traits.hpp>

#include <test/utils/from_json.hpp>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <istream>
#include <string>
#include <vector>

namespace json = nlohmann;

namespace kinet::test
{
    namespace
    {
        Block load_test_block(json::json const &j)
        {
            auto const block_rlp = j.at("rlp").get<byte_string>();
            byte_string_view block_rlp_view{block_rlp};
            auto block = rlp::decode_block(block_rlp_view);
            KINET_ASSERT(!block.has_error());
            return block.value();
        }

        BenchmarkTest
        load_benchmark_test_case(std::string const &name, json::json const &j)
        {
            BenchmarkTest bt;
            bt.name = name;

            constexpr auto rev = KINET_ETH_CANCUN;
            bt.json_state = load_blockchain_json_state<EvmTraits<rev>>(j);

            for (auto const &el : j.at("blocks")) {
                bt.test_blocks.emplace_back(load_test_block(el));
            }

            return bt;
        }

    } // namespace

    static void from_json(json::json const &j, std::vector<BenchmarkTest> &o)
    {
        for (auto const &elem_it : j.items()) {
            o.emplace_back(
                load_benchmark_test_case(elem_it.key(), elem_it.value()));
        }
    }

    std::vector<BenchmarkTest> load_benchmark_tests(std::istream &input)
    {
        return json::json::parse(input).get<std::vector<BenchmarkTest>>();
    }

} // namespace kinet::test
