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

#pragma once

#include <category/execution/ethereum/db/db.hpp>
#include <category/execution/ethereum/db/trie_db.hpp>
#include <category/vm/vm.hpp>

#include <kinet/test/config.hpp>

KINET_TEST_NAMESPACE_BEGIN

template <bool page_encoded = false>
struct TestState
{
    kinet::mpt::Db db;
    kinet::TrieDb trie_db;

    TestState()
        : db{page_encoded ? std::make_unique<kinet::KinetInMemoryMachine>()
                          : std::make_unique<kinet::InMemoryMachine>()}
        , trie_db{db}
    {
        KINET_ASSERT(page_encoded == trie_db.is_page_encoded());
    }
};

template <bool page_encoded = false>
using TestStateRef = std::shared_ptr<TestState<page_encoded>>;

KINET_TEST_NAMESPACE_END
