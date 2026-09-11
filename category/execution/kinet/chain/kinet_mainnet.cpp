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

#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/core/hex.hpp>
#include <category/core/int.hpp>
#include <category/core/likely.h>
#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/kinet/chain/kinet_mainnet.hpp>
#include <category/execution/kinet/chain/kinet_mainnet_alloc.hpp>
#include <category/vm/evm/kinet/revision.h>

KINET_NAMESPACE_BEGIN

kinet_revision KinetMainnet::get_kinet_revision(uint64_t const timestamp) const
{
    if (KINET_LIKELY(timestamp >= 1788359400)) { // 2026-09-02T14:30:00.000Z
        return KINET_TEN;
    }
    else if (timestamp >= 1773930600) { // 2026-03-19T14:30:00.000Z
        return KINET_NINE;
    }
    else if (timestamp >= 1763649000) { // 2025-11-20T14:30:00.000Z
        return KINET_EIGHT;
    }
    else if (timestamp >= 1762525800) { // 2025-11-07T14:30:00.000Z
        return KINET_SEVEN;
    }
    else if (timestamp >= 1762266600) { // 2025-11-04T14:30:00.000Z
        return KINET_SIX;
    }
    else if (timestamp >= 1755091800) { // 2025-08-13T13:30:00.000Z
        return KINET_THREE;
    }
    return KINET_TWO;
}

uint256_t KinetMainnet::get_chain_id() const
{
    return 143;
}

GenesisState KinetMainnet::get_genesis_state() const
{
    BlockHeader header;
    header.gas_limit = 5000;
    header.extra_data =
        from_hex(
            "5fc30e623b72ee612c7b388f75c562de73ee347cc2437c4562dee137e386dc0d")
            .value();
    header.base_fee_per_gas = 0;
    header.withdrawals_root = NULL_ROOT;
    header.blob_gas_used = 0;
    header.excess_blob_gas = 0;
    header.parent_beacon_block_root = NULL_ROOT;
    return {header, KINET_MAINNET_ALLOC};
}

KINET_NAMESPACE_END
