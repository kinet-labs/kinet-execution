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

static inline unsigned char
get_nibble(unsigned char const *const d, unsigned const n)
{
    unsigned char r = d[n / 2];
    if (n % 2 == 0) {
        r >>= 4;
    }
    else {
        r &= 0xF;
    }
    return r;
}

static inline void
set_nibble(unsigned char *const d, unsigned const n, unsigned char const v)
{
    unsigned char r = d[n / 2];
    if (n % 2 == 0) {
        r &= 0xF;
        r |= (v << 4);
    }
    else {
        r &= 0xF0;
        r |= (v & 0xF);
    }
    d[n / 2] = r;
}
