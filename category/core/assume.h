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

#include <category/core/assert.h>

/// Assert a precondition in debug builds and propagate it to the optimizer
/// in release builds. In NDEBUG mode this enables the compiler to assume
/// `cond` holds and may allow it to eliminate downstream checks, though
/// evaluating `cond` may still emit instructions. Violating `cond` in
/// release is undefined behavior; in debug, the failure is reported via
/// KINET_ASSERT with the condition string, source location, and backtrace.
#ifdef NDEBUG
    #define KINET_ASSUME(cond)                                                 \
        if (!(cond)) {                                                         \
            __builtin_unreachable();                                           \
        }
#else
    #define KINET_ASSUME(cond) KINET_ASSERT(cond)
#endif
