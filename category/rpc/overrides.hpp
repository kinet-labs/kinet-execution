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

#include <category/core/address.hpp>
#include <category/core/bytes.hpp>
#include <category/execution/ethereum/core/withdrawal.hpp>

#include <ankerl/unordered_dense.h>

#include <cstdint>
#include <optional>
#include <vector>

struct kinet_state_override
{
    struct kinet_state_override_object
    {
        std::optional<kinet::uint256_t> balance{std::nullopt};
        std::optional<uint64_t> nonce{std::nullopt};
        std::optional<kinet::byte_string> code{std::nullopt};
        ankerl::unordered_dense::segmented_map<
            kinet::bytes32_t, kinet::bytes32_t>
            state{};
        ankerl::unordered_dense::segmented_map<
            kinet::bytes32_t, kinet::bytes32_t>
            state_diff{};
    };

    ankerl::unordered_dense::segmented_map<
        kinet::Address, kinet_state_override_object>
        override_sets;
};

struct kinet_state_override_vec
{
    size_t const size;
    kinet_state_override *overrides;

    explicit kinet_state_override_vec(size_t size)
        : size(size)
        , overrides(new kinet_state_override[size]())
    {
    }
};

struct kinet_block_override
{
    std::optional<uint64_t> number{std::nullopt};
    std::optional<uint64_t> time{std::nullopt};
    std::optional<uint64_t> gas_limit{std::nullopt};
    std::optional<kinet::Address> fee_recipient{std::nullopt};
    std::optional<kinet::bytes32_t> prev_randao{std::nullopt};
    std::optional<kinet::uint256_t> base_fee_per_gas{std::nullopt};
    std::optional<std::vector<kinet::Withdrawal>> withdrawals{std::nullopt};
};

struct kinet_block_override_vec
{
    size_t const size;
    kinet_block_override *overrides;

    explicit kinet_block_override_vec(size_t size)
        : size(size)
        , overrides(new kinet_block_override[size]())
    {
    }
};
