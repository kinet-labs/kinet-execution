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

#include <category/core/assert.h>
#include <category/core/config.hpp>
#include <category/execution/ethereum/chain/chain.hpp>
#include <category/execution/ethereum/chain/chain_config.h>
#include <category/execution/ethereum/chain/ethereum_mainnet.hpp>
#include <category/execution/ethereum/chain/hive_net.hpp>
#include <category/execution/kinet/chain/chain_factory.hpp>
#include <category/execution/kinet/chain/kinet_chain.hpp>
#include <category/execution/kinet/chain/kinet_devnet.hpp>
#include <category/execution/kinet/chain/kinet_mainnet.hpp>
#include <category/execution/kinet/chain/kinet_testnet.hpp>

#include <memory>

KINET_NAMESPACE_BEGIN

std::unique_ptr<Chain> make_chain(kinet_chain_config const chain_config)
{
    switch (chain_config) {
    case CHAIN_CONFIG_ETHEREUM_MAINNET:
        return std::make_unique<EthereumMainnet>();
    case CHAIN_CONFIG_KINET_DEVNET:
        return std::make_unique<KinetDevnet>();
    case CHAIN_CONFIG_KINET_TESTNET:
        return std::make_unique<KinetTestnet>();
    case CHAIN_CONFIG_KINET_MAINNET:
        return std::make_unique<KinetMainnet>();
    case CHAIN_CONFIG_HIVE_NET:
        return std::make_unique<HiveNet>();
    }
    KINET_ASSERT(false);
}

std::unique_ptr<KinetChain>
make_kinet_chain(kinet_chain_config const chain_config)
{
    switch (chain_config) {
    case CHAIN_CONFIG_KINET_DEVNET:
        return std::make_unique<KinetDevnet>();
    case CHAIN_CONFIG_KINET_TESTNET:
        return std::make_unique<KinetTestnet>();
    case CHAIN_CONFIG_KINET_MAINNET:
        return std::make_unique<KinetMainnet>();
    case CHAIN_CONFIG_ETHEREUM_MAINNET:
    case CHAIN_CONFIG_HIVE_NET:
        KINET_ABORT_PRINTF(
            "expected a Kinet chain config, got %d", chain_config);
    }
    KINET_ASSERT(false);
}

KINET_NAMESPACE_END
