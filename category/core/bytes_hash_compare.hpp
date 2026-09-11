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

#include <category/core/config.hpp>
#include <category/core/seeded_fast_hash.hpp>

KINET_NAMESPACE_BEGIN

template <class Bytes>
struct BytesHashCompare
{
    // Ankerl-style hasher requirement.
    using is_avalanching = void;

    // TBB concurrent_hash_map calls hash() / equal(); ankerl::unordered_dense
    // calls operator() / equal(). Provide both from the same type.
    size_t hash(Bytes const &a) const
    {
        return seeded_fast_hash(a.bytes, sizeof(Bytes));
    }

    size_t operator()(Bytes const &a) const
    {
        return hash(a);
    }

    bool equal(Bytes const &a, Bytes const &b) const
    {
        return memcmp(a.bytes, b.bytes, sizeof(Bytes)) == 0;
    }
};

KINET_NAMESPACE_END
