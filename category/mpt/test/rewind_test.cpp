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

#include <category/core/test_util/gtest_signal_stacktrace_printer.hpp> // NOLINT
#include <category/mpt/test/test_fixtures_base.hpp>
#include <category/mpt/trie.hpp>
#include <category/mpt/util.hpp>

#include <iostream>
#include <ostream>

struct RewindTest
    : public kinet::test::FillDBWithChunksGTest<
          kinet::test::FillDBWithChunksConfig{
              .chunks_to_fill = 5,
              .history_len = 65535,
              .updates_per_block = 1,
              .use_anonymous_inode = false}>
{
};

TEST_F(RewindTest, works)
{
    auto const path = this->state()->pool.devices()[0].current_path();
    std::cout << "DB is at " << path << ". Closing DB ..." << std::endl;
    auto &aux = this->state()->aux;
    auto &io = this->state()->io;
    auto const max_version = aux.metadata_ctx().db_history_max_version();
    aux.metadata_ctx().set_latest_finalized_version(max_version);
    aux.metadata_ctx().set_latest_verified_version(max_version);
    aux.metadata_ctx().set_latest_voted(100, kinet::bytes32_t{100});
    std::cout << "Reopening DB ..." << std::endl;
    aux.init(io, 20000);
    std::cout << "Rewinding DB to latest version " << max_version << "..."
              << std::endl;
    aux.rewind_to_version(max_version);
    EXPECT_TRUE(aux.metadata_ctx().version_is_valid_ondisk(max_version));
    EXPECT_EQ(aux.metadata_ctx().get_latest_finalized_version(), max_version);
    EXPECT_EQ(aux.metadata_ctx().get_latest_verified_version(), max_version);
    EXPECT_EQ(aux.metadata_ctx().get_latest_voted_version(), 100);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{100});

    std::cout << "Rewinding DB to 9990 ..." << std::endl;
    aux.rewind_to_version(9990);
    std::cout << "\nAfter rewind to 9990:\n";
    this->state()->print(std::cout);
    EXPECT_EQ(0, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(9990, aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(9990, aux.metadata_ctx().get_latest_finalized_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_verified_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
    std::cout << "\nClosing DB ..." << std::endl;
    std::cout
        << "Reopening DB to check valid versions are what they should be ..."
        << std::endl;
    aux.init(io);
    EXPECT_EQ(0, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(9990, aux.metadata_ctx().db_history_max_version());
    // rewind to latest is noop
    EXPECT_EQ(9990, aux.metadata_ctx().get_latest_finalized_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_verified_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
    std::cout << "Setting max history to 9000 and reopening ..." << std::endl;
    aux.init(io, 9000);
    EXPECT_EQ(991, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(9990, aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
    aux.rewind_to_version(9900);
    EXPECT_EQ(991, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(9900, aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
    aux.init(io);
    EXPECT_EQ(991, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(9900, aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
    aux.rewind_to_version(991);
    EXPECT_EQ(991, aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(991, aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(991, aux.metadata_ctx().get_latest_finalized_version());
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_verified_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_version(),
        kinet::mpt::INVALID_BLOCK_NUM);
    EXPECT_EQ(
        aux.metadata_ctx().get_latest_voted_block_id(), kinet::bytes32_t{});
}

TEST_F(RewindTest, clear_db)
{
    auto &aux = this->state()->aux;
    aux.clear_ondisk_db();
    EXPECT_EQ(
        kinet::mpt::INVALID_BLOCK_NUM,
        aux.metadata_ctx().db_history_min_valid_version());
    EXPECT_EQ(
        kinet::mpt::INVALID_BLOCK_NUM,
        aux.metadata_ctx().db_history_max_version());
    EXPECT_EQ(
        aux.metadata_ctx().main()->fast_list.begin,
        aux.metadata_ctx().main()->fast_list.end);
    EXPECT_EQ(
        aux.metadata_ctx().main()->slow_list.begin,
        aux.metadata_ctx().main()->slow_list.end);
}

struct RewindTestFillOne
    : public kinet::test::FillDBWithChunksGTest<
          kinet::test::FillDBWithChunksConfig{
              .chunks_to_fill = 1,
              .history_len = 65535,
              .updates_per_block = 1,
              .use_anonymous_inode = false}>
{
};

TEST_F(
    RewindTestFillOne,
    works_when_fast_writer_chunk_is_ahead_of_last_root_offset_chunk)
{
    // Test case to cover the case where fast writer is advanced to a newer
    // chunk than the latest root offset is at
    auto const path = this->state()->pool.devices()[0].current_path();
    auto &aux = this->state()->aux;
    auto const latest_root_offset = aux.metadata_ctx().get_latest_root_offset();
    std::cout << "DB is at " << path << ". Last root offset ["
              << latest_root_offset.id << ", " << latest_root_offset.offset
              << "]. " << std::endl;

    // advance fast writer head to the next chunk
    auto const fast_writer_offset = aux.node_writer_fast->sender().offset();
    auto const *ci = aux.metadata_ctx().main()->free_list_end();
    ASSERT_TRUE(ci != nullptr);
    auto const idx = ci->index(aux.metadata_ctx().main());
    aux.metadata_ctx().remove(idx);
    aux.metadata_ctx().append(kinet::mpt::UpdateAux::chunk_list::fast, idx);
    kinet::async::chunk_offset_t const new_fast_writer_offset{idx, 0};
    aux.metadata_ctx().advance_db_offsets_to(
        new_fast_writer_offset, aux.node_writer_slow->sender().offset());
    std::cout << "Advanced start of fast list offset on disk from ["
              << fast_writer_offset.id << ", " << fast_writer_offset.offset
              << "] to the beginning of a new chunk, id: " << idx << std::endl;

    std::cout << "Closing and reopening Db ...\n" << std::endl;
    // verifies reinitialization succeeds
    aux.init(this->state()->io);
}
