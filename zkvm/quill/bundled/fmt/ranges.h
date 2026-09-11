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

// zkVM shadow of <quill/bundled/fmt/ranges.h>. Quill is dropped from the
// guest link (fmt aliases to std::, see zkvm/category/core/log.hpp), so the
// host fmt headers that #include this quill-bundled fmtlib range support
// resolve here instead. Intentionally empty; the guest formatters that need
// range formatting are shadowed individually to avoid fmt::join.
#pragma once
