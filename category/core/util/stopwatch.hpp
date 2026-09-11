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

#include <chrono>
#include <cstdint>

KINET_NAMESPACE_BEGIN

template <typename Duration = std::chrono::nanoseconds>
class Stopwatch final
{
    std::chrono::time_point<std::chrono::steady_clock> const begin_;

public:
    Stopwatch()
        : begin_{std::chrono::steady_clock::now()}
    {
    }

    Duration elapsed() const
    {
        return std::chrono::duration_cast<Duration>(
            std::chrono::steady_clock::now() - begin_);
    }
};

KINET_NAMESPACE_END
