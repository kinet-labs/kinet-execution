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

#include <category/core/assert.h>
#include <category/core/config.hpp>
#include <category/core/hex.hpp>
#include <category/core/int.hpp>
#include <category/execution/ethereum/chain/chain.hpp>
#include <category/execution/ethereum/chain/genesis_state.hpp>
#include <category/execution/kinet/chain/kinet_devnet.hpp>
#include <category/execution/kinet/chain/kinet_devnet_alloc.hpp>
#include <category/vm/evm/kinet/revision.h>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <system_error>

KINET_NAMESPACE_BEGIN

kinet_revision KinetDevnet::get_kinet_revision(uint64_t const timestamp) const
{
    // Fork timestamp (UNIX seconds) from KINET_DEVNET_FORK_TS; unset
    // defaults to 0, so the chain is KINET_NEXT from genesis as before. A
    // set-but-unparseable value aborts rather than silently parsing as 0.
    static auto const next_at = []() -> uint64_t {
        char const *const env = std::getenv("KINET_DEVNET_FORK_TS");
        if (env == nullptr || *env == '\0') {
            return uint64_t{0};
        }
        char const *const end = env + std::strlen(env);
        uint64_t value = 0;
        auto const [ptr, ec] = std::from_chars(env, end, value);
        KINET_ASSERT_PRINTF(
            ec == std::errc{} && ptr == end,
            "KINET_DEVNET_FORK_TS must be a decimal UNIX timestamp, got "
            "\"%s\"",
            env);
        return value;
    }();
    return timestamp >= next_at ? KINET_NEXT : KINET_NINE;
}

uint256_t KinetDevnet::get_chain_id() const
{
    return 20143;
};

GenesisState KinetDevnet::get_genesis_state() const
{
    BlockHeader header;
    header.difficulty = 17179869184;
    header.gas_limit = 5000;
    store_be(header.nonce.data(), uint64_t{66});
    header.extra_data = from_hex("0x11bbe8db4e347b4e8c937c1c8370e4b5ed33a"
                                 "db3db69cbdb7a38e1e50b1b82fa")
                            .value();
    return {header, KINET_DEVNET_ALLOC};
}

KINET_NAMESPACE_END
