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

#include <category/execution/ethereum/chain/chain_config.h>
#include <category/statesync/statesync_messages.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern unsigned const KINET_SQPOLL_DISABLED;

struct kinet_statesync_client;
struct kinet_statesync_client_context;

// chain_config must be a Kinet chain
struct kinet_statesync_client_context *kinet_statesync_client_context_create(
    enum kinet_chain_config chain_config, char const *const *dbname_paths,
    size_t len, unsigned sq_thread_cpu, struct kinet_statesync_client *,
    void (*statesync_send_request)(
        struct kinet_statesync_client *, struct kinet_sync_request));

uint8_t kinet_statesync_client_prefix_bytes();

size_t kinet_statesync_client_prefixes();

bool kinet_statesync_client_has_reached_target(
    struct kinet_statesync_client_context const *);

void kinet_statesync_client_handle_new_peer(
    struct kinet_statesync_client_context *, uint64_t prefix, uint32_t version);

void kinet_statesync_client_handle_target(
    struct kinet_statesync_client_context *, unsigned char const *, uint64_t);

bool kinet_statesync_client_handle_upsert(
    struct kinet_statesync_client_context *, uint64_t prefix,
    enum kinet_sync_type, unsigned char const *, uint64_t);

void kinet_statesync_client_handle_done(
    struct kinet_statesync_client_context *, struct kinet_sync_done);

bool kinet_statesync_client_finalize(struct kinet_statesync_client_context *);

void kinet_statesync_client_context_destroy(
    struct kinet_statesync_client_context *);

#ifdef __cplusplus
}
#endif
