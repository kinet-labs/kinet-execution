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

#include <category/core/address.hpp>
#include <category/core/config.hpp>
#include <category/core/int.hpp>
#include <category/execution/ethereum/core/receipt.hpp>
#include <category/execution/ethereum/trace/call_frame.hpp>

#include <evmc/evmc.hpp>

#include <cstdint>
#include <span>

KINET_NAMESPACE_BEGIN

struct Transaction;

struct CallTracerBase
{
    void on_enter(evmc_message const &) noexcept {}

    void on_exit(evmc::Result const &) noexcept {}

    void on_log(Receipt::Log) noexcept {}

    void on_self_destruct(
        Address const &, Address const &, uint256_t const &) noexcept
    {
    }

    void on_finish(uint64_t) noexcept {}

    void reset() noexcept {}

    std::span<CallFrame const> get_call_frames() const noexcept
    {
        return {};
    }
};

using NoopCallTracer = CallTracerBase;

KINET_NAMESPACE_END
