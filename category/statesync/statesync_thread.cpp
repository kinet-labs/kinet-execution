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

#include <category/statesync/statesync_thread.hpp>

#include <category/mpt/ondisk_db_config.hpp>

#include <pthread.h>

KINET_NAMESPACE_BEGIN

StateSyncServer::StateSyncServer(StateSyncServerConfig const &config)
    : ctx{std::make_unique<kinet_statesync_server_context>(*config.triedb)}
    , server{kinet_statesync_server_create(
          ctx.get(), config.network, &kinet::statesync_server_recv,
          &kinet::statesync_server_send_upsert,
          &kinet::statesync_server_send_done)}
    , thread{[this, config](std::stop_token const token) {
        pthread_setname_np(pthread_self(), "statesync");

        mpt::AsyncIOContext io_ctx{mpt::ReadOnlyOnDiskDbConfig{
            .sq_thread_cpu = config.ro_sq_thread_cpu,
            .dbname_paths = config.dbname_paths}};
        mpt::Db ro{io_ctx};
        ctx->ro = &ro;

        std::stop_callback stop_cb(
            token, [config]() { config.network->signal_shutdown(); });

        while (!token.stop_requested()) {
            kinet_statesync_server_run_once(server.get());
        }

        ctx->ro = nullptr;
    }}
{
}

std::unique_ptr<StateSyncServer>
make_statesync_server(StateSyncServerConfig const &config)
{
    return std::make_unique<StateSyncServer>(config);
}

KINET_NAMESPACE_END
