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
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#pragma once

#include <category/core/config.hpp>
#include <category/vm/evm/traits.hpp>

KINET_NAMESPACE_BEGIN

struct BlockHeader;
class BlockState;
class ExecutionEventRecorder;

// Block-prelude actions: deploys block-hash-history contract, sets the
// block-hash history, sets EIP-4788 beacon root (Cancun+), runs Kinet's
// staking prelude. Lifted out of execute_block.cpp into its own TU so the
// zkVM guest can pull it without dragging in execute_block.cpp's fiber/
// dispatch_transaction deps.
template <Traits traits>
void execute_block_header(
    BlockState &, BlockHeader const &, ExecutionEventRecorder *);

KINET_NAMESPACE_END
