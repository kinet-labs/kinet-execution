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

#include <evmc/evmc.hpp>

#include <optional>

namespace kinet::vm::evm
{
    evmc::bytes_view delegation_indicator_prefix();

    bool is_delegated(std::span<uint8_t const> code);

    std::optional<Address> resolve_delegation(
        evmc_host_interface const *, evmc_host_context *, Address const &);
}
