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
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// The 32-byte digest produced by the hash primitives in this directory, and by
// the keccak256() / blake3() wrappers in category/core.
//
// The alignas reproduces the alignment of the ethash_hash256 union this type
// replaced. That union declared uint64_t/uint32_t members alongside the byte
// array, which gave it 8-byte alignment; only the byte array was ever used
// here, so the members are gone but the alignment is pinned explicitly rather
// than silently dropped to 1.
struct kinet_hash256
{
    alignas(8) uint8_t bytes[32];
};

static_assert(sizeof(struct kinet_hash256) == 32);
static_assert(alignof(struct kinet_hash256) == 8);

#ifdef __cplusplus
}
#endif
