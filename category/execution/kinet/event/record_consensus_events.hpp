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

#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <cstdint>
#include <span>

KINET_NAMESPACE_BEGIN

class ExecutionEventRecorder;

/// Record the BLOCK_QC event, using the QC for the parent block that is
/// presented in a newly proposed block's header
template <class KinetConsensusBlockHeader>
void record_block_qc(
    ExecutionEventRecorder *, KinetConsensusBlockHeader const &,
    uint64_t finalized_block_num);

/// Record the BLOCK_FINALIZED event
void record_block_finalized(
    ExecutionEventRecorder *, bytes32_t const &block_id, uint64_t block_number);

/// Record a BLOCK_VERIFIED event for each of the given block numbers
void record_block_verified(
    ExecutionEventRecorder *, std::span<uint64_t const> verified_blocks);

KINET_NAMESPACE_END
