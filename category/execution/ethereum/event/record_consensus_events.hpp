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

#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <cstdint>

KINET_NAMESPACE_BEGIN

class ExecutionEventRecorder;

/// Other EVM implementations do not emit consensus events like the Kinet chain,
/// but emitting dummy versions reduces the difference for event consumers that
/// wait to see a particular commitment state (e.g., finalized) before acting.
void record_mock_consensus_events(
    ExecutionEventRecorder *, bytes32_t const &block_id, uint64_t block_number);

KINET_NAMESPACE_END
