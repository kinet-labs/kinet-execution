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

#include <errno.h>
#include <stddef.h>

#include <category/core/event/event_ring_util.h>
#include <category/core/format_err.h>
#include <category/core/srcloc.h>

// Defined in event_ring.c, so we can share kinet_event_ring_get_last_error()
extern thread_local char _g_kinet_event_ring_error_buf[1024];

#define FORMAT_ERRC(...)                                                       \
    kinet_format_err(                                                          \
        _g_kinet_event_ring_error_buf,                                         \
        sizeof(_g_kinet_event_ring_error_buf),                                 \
        &KINET_SOURCE_LOCATION_CURRENT(),                                      \
        __VA_ARGS__)

int kinet_event_ring_query_flocks(
    int, struct kinet_event_flock_info *, size_t *)
{
    return FORMAT_ERRC(ENOSYS, "function not available on non-Linux platforms");
}
