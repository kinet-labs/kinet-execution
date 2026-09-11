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

#include <category/statesync/statesync_messages.h>

#include <sys/types.h>

struct kinet_statesync_server;
struct kinet_statesync_server_context;
struct kinet_statesync_server_network;

struct kinet_statesync_server *kinet_statesync_server_create(
    struct kinet_statesync_server_context *,
    struct kinet_statesync_server_network *,
    ssize_t (*statesync_server_recv)(
        struct kinet_statesync_server_network *, unsigned char *, size_t),
    void (*statesync_server_send_upsert)(
        struct kinet_statesync_server_network *, enum kinet_sync_type,
        unsigned char const *v1, uint64_t size1, unsigned char const *v2,
        uint64_t size2),
    void (*statesync_server_send_done)(
        struct kinet_statesync_server_network *, struct kinet_sync_done));

void kinet_statesync_server_run_once(struct kinet_statesync_server *);

void kinet_statesync_server_destroy(struct kinet_statesync_server *);
