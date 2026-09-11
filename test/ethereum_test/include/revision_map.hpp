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

#include <category/vm/evm/kinet/revision.h>
#include <category/vm/evm/revision.h>
#include <kinet/test/config.hpp>

#include <evmc/evmc.h>

#include <string>
#include <unordered_map>
#include <variant>

KINET_TEST_NAMESPACE_BEGIN

inline std::unordered_map<
    std::string, std::variant<kinet_eth_revision, kinet_revision>> const
    revision_map = {
        {"Berlin", KINET_ETH_BERLIN},
        {"London", KINET_ETH_LONDON},
        {"Merge", KINET_ETH_PARIS},
        {"Paris", KINET_ETH_PARIS},
        {"Shanghai", KINET_ETH_SHANGHAI},
        {"Cancun", KINET_ETH_CANCUN},
        {"Prague", KINET_ETH_PRAGUE},
        {"Osaka", KINET_ETH_OSAKA},
        {"Amsterdam", KINET_ETH_AMSTERDAM},
        {"BPO1", KINET_ETH_OSAKA},
        {"BPO2", KINET_ETH_OSAKA},
        {"OsakaToBPO1AtTime15k", KINET_ETH_OSAKA},
        {"BPO1ToBPO2AtTime15k", KINET_ETH_OSAKA},
        {"KINET_ZERO", KINET_ZERO},
        {"KINET_ONE", KINET_ONE},
        {"KINET_TWO", KINET_TWO},
        {"KINET_THREE", KINET_THREE},
        {"KINET_FOUR", KINET_FOUR},
        {"KINET_FIVE", KINET_FIVE},
        {"KINET_SIX", KINET_SIX},
        {"KINET_SEVEN", KINET_SEVEN},
        {"KINET_EIGHT", KINET_EIGHT},
        {"KINET_NINE", KINET_NINE},
        {"KINET_TEN", KINET_TEN},
        {"KINET_NEXT", KINET_NEXT}};

KINET_TEST_NAMESPACE_END
