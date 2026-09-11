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

#ifdef __cplusplus
extern "C"
{
#endif

#include <category/core/likely.h>

extern __thread int tl_tid;

void init_tl_tid();

static inline int get_tl_tid()
{
    if (KINET_UNLIKELY(!tl_tid)) {
        init_tl_tid();
    }
    return tl_tid;
}

#ifdef __cplusplus
}
#endif
