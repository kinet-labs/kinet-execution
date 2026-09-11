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

#include <category/core/address.hpp>
#include <category/core/config.hpp>
#include <category/execution/ethereum/precompiles.hpp>
#include <category/execution/ethereum/trace/call_tracer.hpp>
#include <category/vm/evm/kinet/revision.h>
#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.hpp>

#include <optional>

KINET_NAMESPACE_BEGIN

class State;

template <Traits traits>
bool is_precompile(Address const &);

template <Traits traits>
std::optional<evmc::Result>
check_call_precompile(State &, CallTracerBase &, evmc_message const &msg);

KINET_NAMESPACE_END
