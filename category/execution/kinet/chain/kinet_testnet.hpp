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

#include <category/core/config.hpp>
#include <category/core/int.hpp>
#include <category/execution/ethereum/chain/genesis_state.hpp>
#include <category/execution/kinet/chain/kinet_chain.hpp>
#include <category/vm/evm/kinet/revision.h>

KINET_NAMESPACE_BEGIN

struct KinetTestnet : KinetChain
{
    virtual kinet_revision
    get_kinet_revision(uint64_t timestamp) const override;

    virtual uint256_t get_chain_id() const override;

    virtual GenesisState get_genesis_state() const override;
};

KINET_NAMESPACE_END
