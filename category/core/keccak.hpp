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
#include <category/crypto/hash256.h>
#include <category/crypto/keccak.h>

KINET_NAMESPACE_BEGIN

inline kinet_hash256 keccak256(byte_string_view const bytes)
{
    kinet_hash256 hash;
    kinet_keccak256(bytes.data(), bytes.size(), hash.bytes);
    return hash;
}

template <size_t N>
inline kinet_hash256 keccak256(unsigned char const (&a)[N])
{
    return keccak256(to_byte_string_view(a));
}

KINET_NAMESPACE_END
