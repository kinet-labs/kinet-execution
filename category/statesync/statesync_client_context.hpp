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

#pragma once

#include <category/core/address.hpp>
#include <category/core/byte_string.hpp>
#include <category/core/bytes.hpp>
#include <category/execution/ethereum/chain/chain_config.h>
#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/ethereum/db/trie_db.hpp>
#include <category/execution/ethereum/db/util.hpp>
#include <category/execution/kinet/chain/kinet_chain.hpp>
#include <category/mpt/db.hpp>
#include <category/statesync/statesync_protocol.hpp>

#include <ankerl/unordered_dense.h>

#include <array>
#include <filesystem>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

struct kinet_statesync_client;
struct kinet_sync_request;

struct kinet_statesync_client_context
{
    template <class K, class V>
    using Map = ankerl::unordered_dense::segmented_map<K, V>;

    using StorageDeltas = Map<kinet::bytes32_t, kinet::bytes32_t>;

    using StateDelta = std::pair<kinet::Account, StorageDeltas>;

    // Chain instance for revision lookups and determine whether the slot or
    // page encoded db are canonical.
    std::unique_ptr<kinet::KinetChain const> chain;

    kinet::mpt::Db db;
    kinet::TrieDb tdb;

    std::unique_ptr<kinet::mpt::Db> secondary_db;
    std::unique_ptr<kinet::TrieDb> secondary_tdb;

    std::vector<std::pair<uint64_t, uint64_t>> progress;
    std::vector<std::unique_ptr<kinet::StatesyncProtocol>> protocol;
    std::array<kinet::BlockHeader, 256> hdrs;
    kinet::BlockHeader tgrt;
    uint64_t current;
    Map<kinet::Address, StorageDeltas> buffered;
    ankerl::unordered_dense::segmented_set<kinet::bytes32_t> seen_code;
    Map<kinet::bytes32_t, kinet::byte_string> code;
    Map<kinet::Address, std::optional<StateDelta>> deltas;
    uint64_t n_upserts;
    kinet_statesync_client *sync;
    void (*statesync_send_request)(
        struct kinet_statesync_client *, struct kinet_sync_request);

    kinet_statesync_client_context(
        kinet_chain_config chain_config,
        std::vector<std::filesystem::path> dbname_paths,
        std::optional<unsigned> sq_thread_cpu, unsigned wr_buffers,
        kinet_statesync_client *,
        void (*statesync_send_request)(
            struct kinet_statesync_client *, struct kinet_sync_request));

    void commit();

private:
    void prepare_current_state();
};
