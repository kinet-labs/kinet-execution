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

// zkVM mirror: exceptions are disabled (-fno-exceptions) on the bare-metal
// zkVM build, so KINET_THROW falls back to zkvm_halt(1), which must always
// be marked as noreturn to preserve throw control flow behavior.
#include <zkvm/core/zkvm_halt.h>

#define KINET_THROW(exc, ...) zkvm_halt(1)
#define KINET_TRY
#define KINET_CATCH(...) if constexpr (false)
