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

#include <stddef.h>
#include <stdint.h>

#include <category/core/event/event_metadata.h>
#include <category/core/event/test_event_ctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct kinet_event_metadata const g_kinet_test_event_metadata[4] = {

    [KINET_TEST_EVENT_NONE] =
        {.event_type = KINET_TEST_EVENT_NONE,
         .c_name = "NONE",
         .description = "Reserved code so that 0 remains invalid"},

    [KINET_TEST_EVENT_RECORD_ERROR] =
        {.event_type = KINET_TEST_EVENT_RECORD_ERROR,
         .c_name = "RECORD_ERROR",
         .description = "Reserved event type used for recording errors"},

    [KINET_TEST_EVENT_COUNTER] =
        {.event_type = KINET_TEST_EVENT_COUNTER,
         .c_name = "TEST_COUNTER",
         .description = "A test suite event that counts"},

    [KINET_TEST_EVENT_VLT] =
        {.event_type = KINET_TEST_EVENT_VLT,
         .c_name = "TEST_VLT",
         .description =
             "A test suite event that records variable-length trailing arrays"},

};

uint8_t const g_kinet_test_event_schema_hash[32] = {};

#ifdef __cplusplus
} // extern "C"
#endif
