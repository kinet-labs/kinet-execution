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

#include <category/core/basic_formatter.hpp>
#include <category/core/log.hpp>
#include <category/mpt/nibbles_view.hpp>

template <>
struct quill::Codec<kinet::mpt::NibblesView>
    : quill::DirectFormatCodec<kinet::mpt::NibblesView>
{
};

template <>
struct fmt::formatter<kinet::mpt::NibblesView> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::mpt::NibblesView const &value, FormatContext &ctx) const
    {
        fmt::format_to(ctx.out(), "0x");
        for (auto i = 0u; i < value.nibble_size(); ++i) {
            fmt::format_to(ctx.out(), "{:01x}", value.get(i));
        }
        return ctx.out();
    }
};
