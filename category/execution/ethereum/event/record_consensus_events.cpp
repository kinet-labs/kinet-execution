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

#include <category/core/config.hpp>
#include <category/execution/ethereum/event/exec_event_ctypes.h>
#include <category/execution/ethereum/event/exec_event_recorder.hpp>
#include <category/execution/ethereum/event/record_consensus_events.hpp>

KINET_NAMESPACE_BEGIN

void record_mock_consensus_events(
    ExecutionEventRecorder *const exec_recorder, bytes32_t const &block_id,
    uint64_t const block_number)
{
    if (exec_recorder != nullptr) {
        ReservedEvent const block_qc =
            exec_recorder->reserve_block_event<kinet_exec_block_qc>(
                KINET_EXEC_BLOCK_QC);
        *block_qc.payload = kinet_exec_block_qc{
            .block_tag = {.id = block_id, .block_number = block_number},
            .round = block_number + 1,
            .epoch = 0};
        exec_recorder->commit(block_qc);

        ReservedEvent const block_finalized =
            exec_recorder->reserve_block_event<kinet_exec_block_finalized>(
                KINET_EXEC_BLOCK_FINALIZED);
        *block_finalized.payload = kinet_exec_block_finalized{
            .id = block_id, .block_number = block_number};
        exec_recorder->commit(block_finalized);

        ReservedEvent const block_verified =
            exec_recorder->reserve_block_event<kinet_exec_block_verified>(
                KINET_EXEC_BLOCK_VERIFIED);
        *block_verified.payload =
            kinet_exec_block_verified{.block_number = block_number};
        exec_recorder->commit(block_verified);
    }
}

KINET_NAMESPACE_END
