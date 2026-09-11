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
#include <category/core/block.hpp>
#include <category/core/fmt/address_fmt.hpp>
#include <category/core/fmt/bytes_fmt.hpp>
#include <category/core/fmt/int_fmt.hpp>
#include <category/core/fmt/receipt_fmt.hpp>
#include <category/core/fmt/transaction_fmt.hpp>
#include <category/core/log.hpp>

KINET_LOG_LOGGABLE(kinet::BlockHeader);

template <>
struct fmt::formatter<kinet::BlockHeader> : public kinet::BasicFormatter
{
    template <typename FormatContext>
    auto format(kinet::BlockHeader const &bh, FormatContext &ctx) const
    {
        fmt::format_to(
            ctx.out(),
            "BlockHeader{{"
            "Parent Hash={} "
            "Ommers Hash={} "
            "Beneficiary Address={} "
            "State Root={} "
            "Transaction Root={} "
            "Receipt Root={} "
            "Logs Bloom=0x{:02x} "
            "Difficulty={} "
            "Block Number={} "
            "Gas Limit={} "
            "Gas Used={} "
            "Timestamp={} "
            "Extra Data=0x{:02x} "
            "Base Fee Per Gas={} "
            "Withdrawal Root={}"
            "}}",
            bh.parent_hash,
            bh.ommers_hash,
            bh.beneficiary,
            bh.state_root,
            bh.transactions_root,
            bh.receipts_root,
            fmt::join(std::as_bytes(std::span(bh.logs_bloom)), ""),
            bh.difficulty,
            bh.number,
            bh.gas_limit,
            bh.gas_used,
            bh.timestamp,
            fmt::join(std::as_bytes(std::span(bh.extra_data)), ""),
            bh.base_fee_per_gas,
            bh.withdrawals_root);
        return ctx.out();
    }
};
