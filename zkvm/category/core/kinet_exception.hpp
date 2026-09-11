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

#include <category/core/config.hpp>
#include <category/core/likely.h>

#include <cstdlib>

// RISC-V build runs with -fno-exceptions, which makes the `throw`
// expression a hard compile error.
#define KINET_ASSERT_THROW(expr, message)                                      \
    do {                                                                       \
        if (KINET_UNLIKELY(!(expr))) {                                         \
            std::abort();                                                      \
        }                                                                      \
    }                                                                          \
    while (0)
