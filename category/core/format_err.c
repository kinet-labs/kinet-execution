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

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <category/core/format_err.h>
#include <category/core/srcloc.h>

static char const *final_path_component(char const *const path)
{
    char const *last = strrchr(path, '/');
    return last == nullptr ? path : last + 1;
}

extern int kinet_vformat_err(
    char *const err_buf, size_t const err_buf_size,
    struct kinet_source_location const *const src, int const err,
    char const *const format, va_list ap)
{
    size_t len;
    int rc = 0;

    if (src != nullptr) {
        rc = snprintf(
            err_buf,
            err_buf_size,
            "%s@%s:%u",
            src->function_name,
            final_path_component(src->file_name),
            src->line);
    }
    len = rc > 0 ? (size_t)rc : 0;
    if (len < err_buf_size - 2) {
        err_buf[len++] = ':';
        err_buf[len++] = ' ';
        rc = vsnprintf(err_buf + len, err_buf_size - len, format, ap);
        if (rc >= 0) {
            len += (size_t)rc;
        }
    }
    if (err != 0 && len < err_buf_size) {
        (void)snprintf(
            err_buf + len, err_buf_size - len, ": %s (%d)", strerror(err), err);
    }
    return err;
}
