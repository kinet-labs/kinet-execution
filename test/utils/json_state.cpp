// Copyright (C) 2025-26 Kinet Labs, Inc.
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

#include "from_json.hpp"

#include <category/execution/ethereum/core/rlp/block_rlp.hpp>
#include <category/execution/ethereum/db/util.hpp>
#include <category/execution/ethereum/state2/block_state.hpp>
#include <category/execution/ethereum/state3/state.hpp>

#include <category/vm/vm.hpp>

#include <memory>

#include <test_resource_data.h>

KINET_TEST_NAMESPACE_BEGIN

template <bool page_encoded>
TestStateRef<page_encoded> JsonState::make_test_state() const
{
    using namespace ::kinet;

    auto test_state = std::make_shared<TestState<page_encoded>>();

    if (!init_state.has_value()) {
        return test_state;
    }

    vm::VM vm;
    BlockState bs{test_state->trie_db, vm};
    State state{bs, Incarnation{0, 0}};
    init_state.value().at("pre").get_to(state);
    bs.merge(state);
    auto [released_state, released_code, _] = std::move(bs).release();
    commit_simple(
        test_state->trie_db,
        *released_state,
        released_code,
        NULL_HASH_BLAKE3,
        header,
        {} /* receipts */,
        {} /* call frames */,
        {} /* senders */,
        {} /* transactions */,
        {} /* ommers */,
        withdrawals);
    test_state->trie_db.finalize(0, NULL_HASH_BLAKE3);
    auto const hash = keccak256(
        rlp::encode_block_header(test_state->trie_db.read_eth_header()));
    KINET_ASSERT(to_bytes(hash) == init_state_hash.value());

    return test_state;
}

template TestStateRef<false> JsonState::make_test_state<false>() const;
template TestStateRef<true> JsonState::make_test_state<true>() const;

std::vector<kinet::Address> JsonState::initial_accounts() const
{
    if (!init_state.has_value()) {
        return {};
    }
    std::vector<kinet::Address> v;
    for (auto const &[s, _] : init_state.value().at("pre").items()) {
        auto const a = kinet::from_hex<Address>(s).value();
        v.push_back(a);
    }
    return v;
}

KINET_TEST_NAMESPACE_END
