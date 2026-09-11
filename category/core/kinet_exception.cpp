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

#include <category/core/backtrace.hpp>
#include <category/core/config.hpp>
#include <category/core/kinet_exception.hpp>

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

extern char const *__progname; // NOLINT(bugprone-reserved-identifier)

KINET_NAMESPACE_BEGIN

KinetException::KinetException(
    char const *const message, char const *const expr,
    char const *const function, char const *const file, long const line)
    : expr_{expr}
    , function_{function}
    , file_{file}
    , line_{line}
    , stack_trace_buffer_{std::malloc(stack_trace_buffer_size)}
{
    if (stack_trace_buffer_) {
        stack_trace_ = stack_backtrace::capture(
            {reinterpret_cast<std::byte *>(stack_trace_buffer_),
             stack_trace_buffer_size});
    }
    (void)std::strncpy(message_, message, message_buffer_size - 1);
    message_[message_buffer_size - 1] = '\0';
}

KinetException::~KinetException()
{
    stack_trace_.reset();
    std::free(stack_trace_buffer_);
}

char const *KinetException::message() const noexcept
{
    return message_;
}

void KinetException::print(int const fd) const noexcept
{
    if (stack_trace_buffer_) {
        stack_trace_->print(fd, 3, true);
    }
    else {
        dprintf(fd, "Memory allocation failed for stack backtrace\n");
    }
    dprintf(
        fd,
        "%s: %s:%ld: %s: Kinet assert throw '%s' failed: '%s'\n",
        __progname,
        file_,
        line_,
        function_,
        expr_,
        message_);
}

KINET_NAMESPACE_END
