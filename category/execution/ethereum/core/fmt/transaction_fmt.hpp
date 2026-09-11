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
#include <category/execution/ethereum/core/fmt/address_fmt.hpp>
#include <category/execution/ethereum/core/fmt/bytes_fmt.hpp>
#include <category/execution/ethereum/core/fmt/int_fmt.hpp>
#include <category/execution/ethereum/core/fmt/signature_fmt.hpp>
#include <category/execution/ethereum/core/transaction.hpp>

KINET_LOG_LOGGABLE(kinet::TransactionType);

KINET_LOG_LOGGABLE(kinet::AccessEntry);

KINET_LOG_LOGGABLE(kinet::AccessList);

KINET_LOG_LOGGABLE(kinet::Transaction);

template <>
struct fmt::formatter<kinet::TransactionType> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::TransactionType const &t, FormatContext &ctx) const
    {
        if (t == kinet::TransactionType::legacy) {
            fmt::format_to(ctx.out(), "legacy");
        }
        else if (t == kinet::TransactionType::eip2930) {
            fmt::format_to(ctx.out(), "eip2930");
        }
        else if (t == kinet::TransactionType::eip1559) {
            fmt::format_to(ctx.out(), "eip1559");
        }
        else {
            fmt::format_to(ctx.out(), "Unknown Transaction Type");
        }
        return ctx.out();
    }
};

template <>
struct fmt::formatter<kinet::AccessEntry> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::AccessEntry const &ae, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "AccessEntry{{"
            "Address={} "
            "Keys={}"
            "}}",
            ae.a,
            ae.keys);

        return ctx.out();
    }
};

template <>
struct fmt::formatter<kinet::Transaction> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::Transaction const &tx, FormatContext &ctx) const
    {
        auto const &sender = kinet::recover_sender(tx);
        fmt::format_to(
            ctx.out(),
            "Transaction{{"
            "sender={} "
            "sc={} "
            "nonce={} "
            "max_priority_fee_per_gas={} "
            "max_fee_per_gas={} "
            "gas_limit={} "
            "value={} "
            "to={} "
            "type={} "
            "data=0x{:02x} "
            "access_list={}"
            "}} ",
            sender,
            tx.sc,
            tx.nonce,
            tx.max_priority_fee_per_gas,
            tx.max_fee_per_gas,
            tx.gas_limit,
            tx.value,
            tx.to,
            tx.type,
            fmt::join(std::as_bytes(std::span(tx.data)), ""),
            tx.access_list);

        return ctx.out();
    }
};
