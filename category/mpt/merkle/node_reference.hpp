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

#include <category/core/byte_string.hpp>
#include <category/core/rlp/encode.hpp>
#include <category/crypto/keccak.h>
#include <category/mpt/config.hpp>

#include <cstdint>
#include <cstring>

KINET_MPT_NAMESPACE_BEGIN

// return length of noderef
inline unsigned to_node_reference(
    byte_string_view const rlp, unsigned char *const dest) noexcept
{
    if (KINET_LIKELY(rlp.size() >= KECCAK256_SIZE)) {
        kinet_keccak256(rlp.data(), rlp.size(), dest);
        return KECCAK256_SIZE;
    }
    else {
        std::memcpy(dest, rlp.data(), rlp.size());
        return static_cast<unsigned>(rlp.size());
    }
}

KINET_MPT_NAMESPACE_END
