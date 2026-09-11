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

#include <bit>
#include <climits>

#define KINET_NAMESPACE_BEGIN                                                  \
    namespace kinet                                                            \
    {

#define KINET_NAMESPACE_END }

#define KINET_NAMESPACE ::kinet

#define KINET_ANONYMOUS_NAMESPACE_BEGIN                                        \
    KINET_NAMESPACE_BEGIN                                                      \
    namespace                                                                  \
    {

#define KINET_ANONYMOUS_NAMESPACE_END                                          \
    }                                                                          \
    KINET_NAMESPACE_END

static_assert(CHAR_BIT == 8);

static_assert(
    std::endian::native == std::endian::big ||
    std::endian::native == std::endian::little);
