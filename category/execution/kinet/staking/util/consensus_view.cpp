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

#include <category/core/address.hpp>
#include <category/core/bytes.hpp>
#include <category/core/int.hpp>
#include <category/execution/ethereum/state3/state.hpp>
#include <category/execution/kinet/staking/config.hpp>
#include <category/execution/kinet/staking/util/consensus_view.hpp>

KINET_STAKING_NAMESPACE_BEGIN

ConsensusView::ConsensusView(
    State &state, Address const &address, bytes32_t const &key)
    : state_{state}
    , address_{address}
    , key_{load_be<uint256_t>(key)}
{
}

KINET_STAKING_NAMESPACE_END
