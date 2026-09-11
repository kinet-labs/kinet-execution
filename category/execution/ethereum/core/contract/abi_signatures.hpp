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

#include <span>
#include <string_view>

#include <cthash/sha3/keccak.hpp>

KINET_NAMESPACE_BEGIN

consteval uint32_t abi_encode_selector(std::string_view const function_name)
{
    auto const h =
        cthash::keccak_256{}.update(std::span{function_name}).final();

    // convert to big endian
    return (static_cast<uint32_t>(h[0]) << 24) |
           (static_cast<uint32_t>(h[1]) << 16) |
           (static_cast<uint32_t>(h[2]) << 8) | static_cast<uint32_t>(h[3]);
}

consteval bytes32_t
abi_encode_event_signature(std::string_view const event_name)
{
    auto const h = cthash::keccak_256{}.update(std::span{event_name}).final();
    return std::bit_cast<bytes32_t>(h);
}

KINET_NAMESPACE_END
