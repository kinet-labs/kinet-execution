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

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct KinetRunloopWord
{
    uint8_t bytes[32];
};

struct KinetRunloopAddress
{
    uint8_t bytes[20];
};

// Opaque runloop structure:
typedef void KinetRunloop;

// Make a new runloop client
KinetRunloop *kinet_runloop_new(
    uint64_t chain_id, char const *ledger_path, char const *db_path);

// Deallocate a runloop client
void kinet_runloop_delete(KinetRunloop *);

// Execute and finalize `nblocks` number of blocks.
void kinet_runloop_run(KinetRunloop *, uint64_t nblocks);

// Set balance of the account with given address.
void kinet_runloop_set_balance(
    KinetRunloop *, KinetRunloopAddress const *, KinetRunloopWord const *);

// Get balance of the account with given address.
// Balance is stored in `result_balance`
void kinet_runloop_get_balance(
    KinetRunloop *, KinetRunloopAddress const *,
    KinetRunloopWord *result_balance);

// Store current primary state root in `result_state_root`.
void kinet_runloop_get_primary_state_root(
    KinetRunloop *, KinetRunloopWord *result_state_root);

// Store current secondary state root in `result_state_root`.
void kinet_runloop_get_secondary_state_root(
    KinetRunloop *, KinetRunloopWord *result_state_root);

// Dump the current state of the database to stdout
void kinet_runloop_dump(KinetRunloop *);

#ifdef __cplusplus
}
#endif
