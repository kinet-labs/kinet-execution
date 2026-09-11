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

#include <category/core/basic_formatter.hpp>
#include <category/core/log.hpp>
#include <category/execution/ethereum/types/incarnation.hpp>

#include <type_traits>

KINET_LOG_LOGGABLE(kinet::Incarnation);

template <>
struct fmt::formatter<kinet::Incarnation> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::Incarnation const &incarnation, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "Incarnation{{"
            "block={}, "
            "tx={}"
            "}}",
            incarnation.get_block(),
            incarnation.get_tx());
        return ctx.out();
    }
};
