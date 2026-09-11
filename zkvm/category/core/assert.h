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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include_next <category/core/assert.h>

#include <zkvm/core/zkvm_halt.h>

#define kinet_assertion_failed(expr, function, file, line, msg) zkvm_halt(1)

#undef KINET_ASSERT_PRINTF
#define KINET_ASSERT_PRINTF(expr, format, ...)                                 \
    if (KINET_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        zkvm_halt(1);                                                          \
    }

#undef KINET_ABORT_PRINTF
#define KINET_ABORT_PRINTF(format, ...) zkvm_halt(1)
