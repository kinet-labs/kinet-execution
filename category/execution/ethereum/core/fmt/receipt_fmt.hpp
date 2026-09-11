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

#include <category/core/basic_formatter.hpp>
#include <category/execution/ethereum/core/fmt/address_fmt.hpp>
#include <category/execution/ethereum/core/fmt/bytes_fmt.hpp>
#include <category/execution/ethereum/core/fmt/transaction_fmt.hpp>
#include <category/execution/ethereum/core/receipt.hpp>

KINET_LOG_LOGGABLE(kinet::Receipt::Log);

KINET_LOG_LOGGABLE(kinet::Receipt);

template <>
struct fmt::formatter<kinet::Receipt::Log> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::Receipt::Log const &l, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "Log{{"
            "Data=0x{:02x} "
            "Topics={} "
            "Address={}"
            "}}",
            fmt::join(std::as_bytes(std::span(l.data)), ""),
            l.topics,
            l.address);
        return ctx.out();
    }
};

template <>
struct fmt::formatter<kinet::Receipt> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::Receipt const &r, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "Receipt{{"
            "Bloom=0x{:02x} "
            "Status={} "
            "Gas Used={} "
            "Transaction Type={} "
            "Logs={}"
            "}}",
            fmt::join(std::as_bytes(std::span(r.bloom)), ""),
            r.status,
            r.gas_used,
            r.type,
            r.logs);
        return ctx.out();
    }
};
