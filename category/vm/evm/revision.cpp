// Copyright (C) 2025-26 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <category/core/assert.h>
#include <category/vm/evm/revision.h>

#include <evmc/evmc.h>

#include <utility>

// Enforce the 1:1 correspondence with evmc_revision that makes the conversions
// below value-preserving casts. If evmc ever renumbers a revision, these fire.
#define KINET_ASSERT_REVISION_EQ(rev)                                          \
    static_assert(                                                             \
        std::to_underlying(KINET_ETH_##rev) == std::to_underlying(EVMC_##rev))

KINET_ASSERT_REVISION_EQ(FRONTIER);
KINET_ASSERT_REVISION_EQ(HOMESTEAD);
KINET_ASSERT_REVISION_EQ(TANGERINE_WHISTLE);
KINET_ASSERT_REVISION_EQ(SPURIOUS_DRAGON);
KINET_ASSERT_REVISION_EQ(BYZANTIUM);
KINET_ASSERT_REVISION_EQ(CONSTANTINOPLE);
KINET_ASSERT_REVISION_EQ(PETERSBURG);
KINET_ASSERT_REVISION_EQ(ISTANBUL);
KINET_ASSERT_REVISION_EQ(BERLIN);
KINET_ASSERT_REVISION_EQ(LONDON);
KINET_ASSERT_REVISION_EQ(PARIS);
KINET_ASSERT_REVISION_EQ(SHANGHAI);
KINET_ASSERT_REVISION_EQ(CANCUN);
KINET_ASSERT_REVISION_EQ(PRAGUE);
KINET_ASSERT_REVISION_EQ(OSAKA);

#undef KINET_ASSERT_REVISION_EQ

// KINET_ETH_AMSTERDAM and the KINET_ETH_EXPERIMENTAL / KINET_ETH_MAX_REVISION
// sentinel above it have no evmc_revision counterpart in the bundled evmc
// (whose enum stops at EVMC_OSAKA followed by EVMC_EXPERIMENTAL == 15), so they
// are not asserted equal above. The per-revision asserts through OSAKA keep the
// bare casts below value-preserving across the evmc-backed range
// (FRONTIER..OSAKA).
//
// KINET_ETH_LATEST_STABLE_REVISION likewise intentionally diverges from
// EVMC_LATEST_STABLE_REVISION (still Cancun in the bundled evmc).

// Map a kinet_eth_revision to evmc_revision at the remaining evmc/evmone
// boundaries (test and benchmark paths). Only FRONTIER..OSAKA are convertible;
// they mirror evmc_revision 1:1 (asserted above).
//
// AMSTERDAM (and the EXPERIMENTAL sentinel above it) have no evmc counterpart.
// Amsterdam support is in progress and its behavior will diverge from OSAKA, so
// it must NOT be silently substituted with another revision here: handing
// evmone OSAKA — or, via a bare cast, EVMC_EXPERIMENTAL — would compare Kinet's
// Amsterdam against the wrong reference semantics. Abort instead until evmc
// gains a real Amsterdam value.
// TODO(amsterdam): convert AMSTERDAM to its evmc revision once one exists.
evmc_revision to_evmc_revision(kinet_eth_revision const rev)
{
    KINET_ASSERT(rev <= KINET_ETH_OSAKA);
    return static_cast<evmc_revision>(std::to_underlying(rev));
}

// The inverse only ever receives real evmc revisions. EVMC_EXPERIMENTAL — which
// a bare cast would turn into AMSTERDAM, since they share the value 15 — is a
// sentinel and is rejected rather than silently misinterpreted.
kinet_eth_revision from_evmc_revision(evmc_revision const rev)
{
    KINET_ASSERT(rev <= EVMC_OSAKA);
    return static_cast<kinet_eth_revision>(std::to_underlying(rev));
}

char const *kinet_eth_revision_to_string(kinet_eth_revision const rev)
{
    switch (rev) {
    case KINET_ETH_FRONTIER:
        return "KINET_ETH_FRONTIER";
    case KINET_ETH_HOMESTEAD:
        return "KINET_ETH_HOMESTEAD";
    case KINET_ETH_TANGERINE_WHISTLE:
        return "KINET_ETH_TANGERINE_WHISTLE";
    case KINET_ETH_SPURIOUS_DRAGON:
        return "KINET_ETH_SPURIOUS_DRAGON";
    case KINET_ETH_BYZANTIUM:
        return "KINET_ETH_BYZANTIUM";
    case KINET_ETH_CONSTANTINOPLE:
        return "KINET_ETH_CONSTANTINOPLE";
    case KINET_ETH_PETERSBURG:
        return "KINET_ETH_PETERSBURG";
    case KINET_ETH_ISTANBUL:
        return "KINET_ETH_ISTANBUL";
    case KINET_ETH_BERLIN:
        return "KINET_ETH_BERLIN";
    case KINET_ETH_LONDON:
        return "KINET_ETH_LONDON";
    case KINET_ETH_PARIS:
        return "KINET_ETH_PARIS";
    case KINET_ETH_SHANGHAI:
        return "KINET_ETH_SHANGHAI";
    case KINET_ETH_CANCUN:
        return "KINET_ETH_CANCUN";
    case KINET_ETH_PRAGUE:
        return "KINET_ETH_PRAGUE";
    case KINET_ETH_OSAKA:
        return "KINET_ETH_OSAKA";
    case KINET_ETH_AMSTERDAM:
        return "KINET_ETH_AMSTERDAM";
    case KINET_ETH_EXPERIMENTAL:
        return "KINET_ETH_EXPERIMENTAL";
    }
    KINET_ABORT("unhandled kinet_eth_revision");
}
