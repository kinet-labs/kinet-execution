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

#include <category/execution/ethereum/db/db_snapshot.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct kinet_db_snapshot_filesystem_write_user_context;

struct kinet_db_snapshot_filesystem_write_user_context *
kinet_db_snapshot_filesystem_write_user_context_create(
    char const *root, uint64_t block);

void kinet_db_snapshot_filesystem_write_user_context_destroy(
    struct kinet_db_snapshot_filesystem_write_user_context *);

uint64_t kinet_db_snapshot_write_filesystem(
    uint64_t shard, kinet_snapshot_type, unsigned char const *bytes, size_t len,
    void *user);

void kinet_db_snapshot_load_filesystem(
    char const *const *dbname_paths, size_t len, unsigned sq_thread_cpu,
    char const *snapshot_dir, uint64_t block, bool load_to_secondary);

#ifdef __cplusplus
}
#endif
