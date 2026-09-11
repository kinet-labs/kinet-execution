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

#include <evmc/evmc.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Kinet's in-tree EVM fork revision enum. This is a drop-in replacement for
// evmc's `evmc_revision`: the enumerators through KINET_ETH_OSAKA mirror
// `evmc_revision` 1:1 (same underlying integer values), which keeps ordering
// comparisons between revisions unchanged. That 1:1 correspondence is
// enforced by static_assert in revision.cpp.
//
// KINET_ETH_AMSTERDAM and above have no `evmc_revision` counterpart in the
// bundled evmc — they are the first future forks grown on this side of the
// boundary, so they are not (and cannot be) asserted equal to any EVMC_* value.
//
// The enum itself carries no evmc dependency. The only tie to evmc is the pair
// of conversion functions below, which are needed solely at the remaining
// evmc/evmone boundaries (test and benchmark paths); they — together with the
// <evmc/evmc.h> include — are removable in one step once evmone is gone, after
// which these enumerators can diverge from evmc and grow future forks freely.
enum kinet_eth_revision
{
    KINET_ETH_FRONTIER = 0,
    KINET_ETH_HOMESTEAD = 1,
    KINET_ETH_TANGERINE_WHISTLE = 2,
    KINET_ETH_SPURIOUS_DRAGON = 3,
    KINET_ETH_BYZANTIUM = 4,
    KINET_ETH_CONSTANTINOPLE = 5,
    KINET_ETH_PETERSBURG = 6,
    KINET_ETH_ISTANBUL = 7,
    KINET_ETH_BERLIN = 8,
    KINET_ETH_LONDON = 9,
    KINET_ETH_PARIS = 10,
    KINET_ETH_SHANGHAI = 11,
    KINET_ETH_CANCUN = 12,
    KINET_ETH_PRAGUE = 13,
    KINET_ETH_OSAKA = 14,
    KINET_ETH_AMSTERDAM = 15,
    KINET_ETH_EXPERIMENTAL = 16,

    // The maximum EVM revision supported.
    KINET_ETH_MAX_REVISION = KINET_ETH_EXPERIMENTAL,

    // The latest known EVM revision with finalized specification.
    KINET_ETH_LATEST_STABLE_REVISION = KINET_ETH_PRAGUE
};

char const *kinet_eth_revision_to_string(enum kinet_eth_revision rev);

// Convert between kinet_eth_revision and evmc's evmc_revision. Needed only at
// the remaining evmc/evmone boundaries (see the note above).
enum evmc_revision to_evmc_revision(enum kinet_eth_revision rev);
enum kinet_eth_revision from_evmc_revision(enum evmc_revision rev);

#ifdef __cplusplus
} // extern "C"
#endif
