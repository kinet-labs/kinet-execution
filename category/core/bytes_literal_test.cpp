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

#include <gtest/gtest.h>

#include <category/core/byte_string.hpp>
#include <category/core/hex.hpp>
#include <category/core/test_util/gtest_signal_stacktrace_printer.hpp> // NOLINT

using namespace ::kinet::literals;

TEST(LiteralTest, variable_length_hex)
{
    EXPECT_EQ((0x123456781234567812345678_bytes).size(), 12);
    EXPECT_EQ(
        0x123456781234567812345678_bytes,
        kinet::byte_string({
            0x12,
            0x34,
            0x56,
            0x78,
            0x12,
            0x34,
            0x56,
            0x78,
            0x12,
            0x34,
            0x56,
            0x78,
        }));

    EXPECT_EQ(
        (0x123456781234567812345678123456781234567812345678_bytes).size(), 24);
    EXPECT_EQ(
        0x123456781234567812345678123456781234567812345678_bytes,
        kinet::byte_string({
            0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78,
            0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78,
            0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78,
        }));

    EXPECT_EQ(
        (0x1234567812345678123456781234567812345678123456781234567812345678_bytes)
            .size(),
        32);
    EXPECT_EQ(
        0x1234567812345678123456781234567812345678123456781234567812345678_bytes,
        kinet::byte_string({
            0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56,
            0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34,
            0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78,
        }));

    // without 0x prefix
    EXPECT_EQ(
        (1234567812345678123456781234567812345678123456781234567812345678_bytes)
            .size(),
        32);
    EXPECT_EQ(
        1234567812345678123456781234567812345678123456781234567812345678_bytes,
        kinet::byte_string({
            0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56,
            0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34,
            0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78,
        }));
}
