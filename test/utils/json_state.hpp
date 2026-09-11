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

#include "test_state.hpp"

#include <nlohmann/json.hpp>

KINET_TEST_NAMESPACE_BEGIN

struct JsonState
{
    kinet::BlockHeader header;
    std::optional<std::vector<Withdrawal>> withdrawals;
    std::optional<nlohmann::json> init_state;
    std::optional<kinet::bytes32_t> init_state_hash;

    template <bool page_encoded = false>
    TestStateRef<page_encoded> make_test_state() const;
    std::vector<kinet::Address> initial_accounts() const;
};

KINET_TEST_NAMESPACE_END
