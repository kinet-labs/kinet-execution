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

#include <category/statesync/statesync_server.h>
#include <category/statesync/statesync_server_context.hpp>
#include <category/statesync/statesync_server_network.hpp>

#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <thread>
#include <vector>

KINET_NAMESPACE_BEGIN

struct StateSyncServerConfig
{
    kinet::TrieDb *triedb;
    kinet_statesync_server_network *network;
    std::optional<int> ro_sq_thread_cpu;
    std::vector<std::filesystem::path> dbname_paths;
};

struct kinet_statesync_server_deleter
{
    void operator()(kinet_statesync_server *const server) const
    {
        if (server != nullptr) {
            kinet_statesync_server_destroy(server);
        }
    }
};

struct StateSyncServer
{
    std::unique_ptr<kinet_statesync_server_context> ctx;
    std::unique_ptr<kinet_statesync_server, kinet_statesync_server_deleter>
        server;
    std::jthread thread;

    explicit StateSyncServer(StateSyncServerConfig const &config);

    StateSyncServer(StateSyncServer const &) = delete;
    StateSyncServer &operator=(StateSyncServer const &) = delete;
    StateSyncServer(StateSyncServer &&) = delete;
    StateSyncServer &operator=(StateSyncServer &&) = delete;
};

std::unique_ptr<StateSyncServer>
make_statesync_server(StateSyncServerConfig const &config);

KINET_NAMESPACE_END
