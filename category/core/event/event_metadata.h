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

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// clang-format off

/// Metadata describing each event in an event domain
struct kinet_event_metadata
{
    uint16_t event_type;      ///< Enumeration constant
    char const *c_name;       ///< Short form C style name
    char const *description;  ///< Text description for UI commands
};

// clang-format on

#ifdef __cplusplus
} // extern "C"
#endif
