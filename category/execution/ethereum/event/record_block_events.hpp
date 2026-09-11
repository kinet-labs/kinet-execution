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

#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/core/int.hpp>
#include <category/core/result.hpp>
#include <category/execution/ethereum/core/block.hpp>

#include <cstddef>
#include <cstdint>

struct kinet_c_secp256k1_pubkey;
struct kinet_c_native_block_input;

KINET_NAMESPACE_BEGIN

class ExecutionEventRecorder;

/// Named pair holding the Ethereum block execution outputs
struct BlockExecOutput
{
    BlockHeader eth_header;
    bytes32_t eth_block_hash;
};

/// Record the start of block execution: emits a BLOCK_START event and
/// sets the block flow sequence number in the recorder
void record_block_start(
    ExecutionEventRecorder *, bytes32_t const &bft_block_id,
    uint256_t const &chain_id, BlockHeader const &,
    bytes32_t const &eth_parent_hash, uint64_t block_round, uint64_t epoch,
    uint128_t epoch_nano_timestamp, size_t txn_count,
    std::optional<kinet_c_secp256k1_pubkey> const &,
    std::optional<kinet_c_native_block_input> const &);

/// Record block execution output events (or an execution error event, if
/// Result::has_error() is true); also clears the active block flow ID
Result<BlockExecOutput>
record_block_result(ExecutionEventRecorder *, Result<BlockExecOutput>);

KINET_NAMESPACE_END
