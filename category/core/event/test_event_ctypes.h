// Copyright (C) 2025 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

/**
 * @file
 *
 * Definitions of events used with the TEST event ring
 */

#include <stdint.h>

#include <category/core/event/event_metadata.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// Each type of event is assigned a unique value in this enumeration
enum kinet_test_event : uint16_t
{
    KINET_TEST_EVENT_NONE,
    KINET_TEST_EVENT_RECORD_ERROR,
    KINET_TEST_EVENT_COUNTER,
    KINET_TEST_EVENT_VLT,
};

/// Event payload for KINET_TEST_EVENT_COUNTER
struct kinet_test_event_counter
{
    uint8_t writer_id;
    uint64_t counter;
};

/// Event payload for KINET_TEST_EVENT_VLT
struct kinet_test_event_vlt
{
    uint32_t vlt_1_length;
    uint32_t vlt_2_length;
};

extern struct kinet_event_metadata const g_kinet_test_event_metadata[4];
extern uint8_t const g_kinet_test_event_schema_hash[32];

#define KINET_EVENT_DEFAULT_TEST_FILE_NAME "event-recorder-test"

#ifdef __cplusplus
} // extern "C"
#endif
