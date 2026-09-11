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

#include <category/execution/ethereum/dispatch_transaction.hpp>
#include <category/execution/kinet/system_sender.hpp>

#include <boost/fiber/future/promise.hpp>
KINET_NAMESPACE_BEGIN

class ExecutionEventRecorder;

template <Traits traits>
Result<Receipt> dispatch_transaction(
    Chain const &chain, uint64_t const i, Transaction const &transaction,
    Address const &sender,
    std::vector<std::optional<Address>> const &authorities,
    BlockHeader const &header, BlockHashBuffer const &block_hash_buffer,
    BlockState &block_state, BlockMetrics &block_metrics,
    boost::fibers::promise<void> &prev, CallTracerBase &call_tracer,
    trace::StateTracer &, ChainContext<traits> const &chain_ctx,
    ExecutionEventRecorder *exec_recorder, bool trace_transfers);

KINET_NAMESPACE_END
