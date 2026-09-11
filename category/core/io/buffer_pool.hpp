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

#include <category/core/io/config.hpp>

KINET_IO_NAMESPACE_BEGIN

class Buffers;

class BufferPool
{
    unsigned char *next_;

public:
    BufferPool(Buffers const &, bool is_read);

    [[gnu::always_inline]] unsigned char *alloc()
    {
        unsigned char *const next = next_;
        if (next) {
            next_ = *reinterpret_cast<unsigned char **>(next);
        }
        return next;
    }

    [[gnu::always_inline]] void release(unsigned char *const next)
    {
        *reinterpret_cast<unsigned char **>(next) = next_;
        next_ = next;
    }
};

static_assert(sizeof(BufferPool) == 8);
static_assert(alignof(BufferPool) == 8);

KINET_IO_NAMESPACE_END
