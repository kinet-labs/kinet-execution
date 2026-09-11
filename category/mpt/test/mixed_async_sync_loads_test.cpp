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

#include "test_fixtures_gtest.hpp"

#include <category/async/connected_operation.hpp>
#include <category/async/erased_connected_operation.hpp>
#include <category/core/assert.h>
#include <category/core/test_util/gtest_signal_stacktrace_printer.hpp> // NOLINT
#include <category/mpt/config.hpp>
#include <category/mpt/detail/timeline.hpp>
#include <category/mpt/find_request_sender.hpp>
#include <category/mpt/node.hpp>
#include <category/mpt/test/test_fixtures_base.hpp>
#include <category/mpt/trie.hpp>

#include <memory>
#include <optional>
#include <utility>

using namespace KINET_MPT_NAMESPACE;

namespace
{
    struct MixedAsyncSyncLoadsTest
        : public kinet::test::FillDBWithChunksGTest<
              kinet::test::FillDBWithChunksConfig{.chunks_to_fill = 1}>
    {
    };

    struct receiver_t
    {
        std::optional<
            kinet::mpt::find_request_sender<>::result_type::value_type>
            res;

        static constexpr bool lifetime_managed_internally = false;

        void set_value(
            kinet::async::erased_connected_operation *,
            kinet::mpt::find_request_sender<>::result_type r)
        {
            KINET_ASSERT(r);
            res = std::move(r).assume_value();
        }
    };
}

TEST_F(MixedAsyncSyncLoadsTest, works)
{
    // Make a new empty DB
    kinet::test::UpdateAux aux{state()->io};
    kinet::test::StateMachineAlwaysMerkle const sm;
    // Load its root
    auto const latest_version = aux.metadata_ctx().db_history_max_version();
    kinet::mpt::Node::SharedPtr const root{kinet::mpt::read_node_blocking(
        aux,
        aux.metadata_ctx().get_root_offset_at_version(latest_version),
        latest_version,
        kinet::mpt::timeline_id::primary)};
    auto const &key = state()->keys.front().first;
    auto const &value = state()->keys.front().first;

    // Initiate an async find of a key
    kinet::mpt::AsyncInflightNodes inflights;
    kinet::mpt::NodeCache node_cache{
        1000 * kinet::mpt::NodeCache::AVERAGE_NODE_SIZE};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    auto state = kinet::async::connect(
        kinet::mpt::find_request_sender<>(
            aux,
            node_cache,
            inflights,
            NodeCursor{root},
            latest_version,
            key,
            true,
            timeline_id::primary),
        receiver_t{});
    state.initiate();

    // Synchronously load the same key
    EXPECT_EQ(
        find_blocking(
            aux,
            NodeCursor{root},
            key,
            latest_version,
            kinet::mpt::timeline_id::primary)
            .first.node->value(),
        value);

    // Let the async find of that key complete
    while (!state.receiver().res) {
        aux.io->poll_blocking();
    }
    EXPECT_EQ(state.receiver().res->first, value);
}
