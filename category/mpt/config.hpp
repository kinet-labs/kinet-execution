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

#include <category/core/config.hpp>

#define KINET_MPT_NAMESPACE_BEGIN                                              \
    KINET_NAMESPACE_BEGIN namespace mpt                                        \
    {

#define KINET_MPT_NAMESPACE_END                                                \
    }                                                                          \
    KINET_NAMESPACE_END

#define KINET_MPT_NAMESPACE ::kinet::mpt

KINET_MPT_NAMESPACE_BEGIN

static constexpr unsigned EMPTY_STRING_RLP_LENGTH = 1;
static constexpr unsigned char RLP_EMPTY_STRING = 0x80;

KINET_MPT_NAMESPACE_END
