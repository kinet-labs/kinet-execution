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

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Components of a statesync protocol version. These are the single source of
// the {major, minor} pairs kinet-bft's StateSyncVersion also names, and bindgen
// exports them to the rust side.
enum kinet_statesync_version_num : uint16_t
{
    KINET_STATESYNC_MAJOR = 1,
    // Client acknowledges each response. Minors 0 and 1 predate that and are no
    // longer spoken; nothing deployed still runs them.
    KINET_STATESYNC_MINOR_2 = 2,
};

// A version as kinet-bft's StateSyncVersion encodes it: major << 16 | minor.
enum kinet_statesync_protocol_version : uint32_t
{
    KINET_STATESYNC_VERSION_1_2 =
        KINET_STATESYNC_MAJOR << 16 | KINET_STATESYNC_MINOR_2,

    KINET_STATESYNC_VERSION_MIN = KINET_STATESYNC_VERSION_1_2,
    KINET_STATESYNC_VERSION = KINET_STATESYNC_VERSION_1_2,
};

uint32_t kinet_statesync_version();

bool kinet_statesync_client_compatible(uint32_t version);

#ifdef __cplusplus
}
#endif
