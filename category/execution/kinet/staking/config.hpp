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

#include <category/core/config.hpp>

#define KINET_STAKING_NAMESPACE_BEGIN                                          \
    KINET_NAMESPACE_BEGIN namespace staking                                    \
    {

#define KINET_STAKING_NAMESPACE_END                                            \
    }                                                                          \
    KINET_NAMESPACE_END

#define KINET_STAKING_ANONYMOUS_NAMESPACE_BEGIN                                \
    KINET_STAKING_NAMESPACE_BEGIN                                              \
    namespace                                                                  \
    {

#define KINET_STAKING_ANONYMOUS_NAMESPACE_END                                  \
    }                                                                          \
    KINET_STAKING_NAMESPACE_END
