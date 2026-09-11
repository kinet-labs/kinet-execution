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
#include <category/execution/ethereum/core/fmt/int_fmt.hpp>
#include <category/execution/ethereum/core/signature.hpp>

KINET_LOG_LOGGABLE(kinet::SignatureAndChain);

template <>
struct fmt::formatter<kinet::SignatureAndChain> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::SignatureAndChain const &sc, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "SignatureAndChain{{"
            "r={} "
            "s={} "
            "chain_id={} "
            "y_parity={}"
            "}}",
            sc.signature.r,
            sc.signature.s,
            sc.chain_id,
            sc.signature.y_parity);
        return ctx.out();
    }
};
