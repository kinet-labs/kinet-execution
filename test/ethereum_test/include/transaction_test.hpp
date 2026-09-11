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

#include <category/vm/evm/kinet/revision.h>
#include <category/vm/evm/revision.h>
#include <kinet/test/config.hpp>

#include <evmc/evmc.hpp>
#include <gtest/gtest.h>

#include <filesystem>
#include <optional>
#include <variant>

KINET_TEST_NAMESPACE_BEGIN

class TransactionTest : public testing::Test
{
private:
    std::filesystem::path const file_;
    std::optional<std::variant<kinet_eth_revision, kinet_revision>> const
        revision_;

public:
    TransactionTest(
        std::filesystem::path const &file,
        std::optional<std::variant<kinet_eth_revision, kinet_revision>> const
            &revision) noexcept
        : file_{file}
        , revision_{revision}
    {
    }

    void TestBody() override;
};

void register_transaction_tests_path(
    std::filesystem::path const &,
    std::optional<std::variant<kinet_eth_revision, kinet_revision>> const &);

void register_transaction_tests(
    std::optional<std::variant<kinet_eth_revision, kinet_revision>> const &);

KINET_TEST_NAMESPACE_END
