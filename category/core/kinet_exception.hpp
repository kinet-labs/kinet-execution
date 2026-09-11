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

#include <category/core/backtrace.hpp>
#include <category/core/config.hpp>
#include <category/core/likely.h>
#include <category/core/throw.hpp>

#include <evmc/evmc.h>

#include <unistd.h>

KINET_NAMESPACE_BEGIN

/// Exception for `KINET_ASSERT_THROW` assertion failure.
class KinetException
{
public:
    KinetException(
        char const *message, char const *expr, char const *function,
        char const *file, long line);

    ~KinetException();

    char const *message() const noexcept;
    void print(int fd = STDERR_FILENO) const noexcept;

    static constexpr size_t message_buffer_size = 128;
    static constexpr size_t stack_trace_buffer_size = 16384;

private:
    char const *expr_;
    char const *function_;
    char const *file_;
    long line_;
    void *stack_trace_buffer_;
    stack_backtrace::ptr stack_trace_;
    char message_[message_buffer_size];
};

// Size of `KinetException` plus the size of exception headers must be
// smaller than 1kB for `KinetException` to fit in an emergency buffer.
// See Itanium C++ ABI: Exception Handling (Revision 1.22), Section 3.4.1.
// The size of an exception header is ~80 bytes according to Itanium C++
// ABI: Exception Handling (Revision 1.22), Section 2.2.1. It therefore
// seems safe to assume that the exception header will not become larger
// than 512 bytes. So if `KinetException` is smaller than 512 bytes, then
// the sum is smaller than 1kB.
static_assert(sizeof(KinetException) < 512);

KINET_NAMESPACE_END

/// Given `bool expr` and 'char const *message', throw
/// `kinet::KinetException` iff `expr` evaluates to `false`.
#define KINET_ASSERT_THROW(expr, message)                                      \
    if (KINET_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        KINET_THROW(                                                           \
            kinet::KinetException,                                             \
            (message),                                                         \
            #expr,                                                             \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__);                                                         \
    }
