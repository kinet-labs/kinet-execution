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

#pragma once

#include <category/execution/kinet/staking/config.hpp>

#include <optional>
#include <vector>

#include <category/core/bytes.hpp>
#include <stdint.h>

KINET_NAMESPACE_BEGIN

namespace mpt
{
    class Db;
}

KINET_NAMESPACE_END

KINET_STAKING_NAMESPACE_BEGIN

struct Validator
{
    uint8_t secp_pubkey[33];
    uint8_t bls_pubkey[48];
    uint256_be_t stake;
};

std::optional<std::vector<Validator>>
read_valset(mpt::Db &db, size_t block_num, uint64_t requested_epoch);

KINET_STAKING_NAMESPACE_END
