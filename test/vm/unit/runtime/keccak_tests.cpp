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

#include "fixture.hpp"

#include <category/core/runtime/uint256.hpp>
#include <category/vm/evm/traits.hpp>
#include <category/vm/runtime/keccak.hpp>
#include <category/vm/runtime/memory.hpp>

using namespace kinet;
using namespace kinet::vm::runtime;
using namespace kinet::vm::compiler::test;

TYPED_TEST(RuntimeTraitsTest, KeccakEmpty)
{
    using traits = TestFixture::Trait;
    ASSERT_EQ(
        TestFixture::call(sha3<traits>, 0, 0),
        0xC5D2460186F7233C927E7DB2DCC703C0E500B653CA82273B7BFAD8045D85A470_u256);
}

TYPED_TEST(RuntimeTraitsTest, KeccakNoExpand)
{
    using traits = TestFixture::Trait;

    auto memory_version = [] {
        if constexpr (is_kinet_trait_v<traits>) {
            if constexpr (traits::kinet_rev() >= KINET_NINE) {
                return Memory::Version::MIP3;
            }
        }
        return Memory::Version::V1;
    }();

    switch (memory_version) {
    case Memory::Version::V1:
        this->ctx_.gas_remaining = 9;
        break;
    case Memory::Version::MIP3:
        this->ctx_.gas_remaining = 6;
        break;
    }

    TestFixture::call(
        mstore<traits>,
        0,
        0xFFFFFFFF00000000000000000000000000000000000000000000000000000000_u256);
    ASSERT_EQ(this->ctx_.gas_remaining, 6);

    ASSERT_EQ(
        TestFixture::call(sha3<traits>, 0, 4),
        0x29045A592007D0C246EF02C2223570DA9522D0CF0F73282C79A1BC8F0BB2C238_u256);
    ASSERT_EQ(this->ctx_.gas_remaining, 0);
}

TYPED_TEST(RuntimeTraitsTest, KeccakExpand)
{
    using traits = TestFixture::Trait;

    auto memory_version = [] {
        if constexpr (is_kinet_trait_v<traits>) {
            if constexpr (traits::kinet_rev() >= KINET_NINE) {
                return Memory::Version::MIP3;
            }
        }
        return Memory::Version::V1;
    }();

    switch (memory_version) {
    case Memory::Version::V1:
        this->ctx_.gas_remaining = 27;
        break;
    case Memory::Version::MIP3:
        this->ctx_.gas_remaining = 19;
        break;
    }

    ASSERT_EQ(
        TestFixture::call(sha3<traits>, 0, 65),
        0xAE61B77B3E4CBAC1353BFA4C59274E3AE531285C24E3CF57C11771ECBF72D9BF_u256);
    ASSERT_EQ(this->ctx_.gas_remaining, 0);
    switch (memory_version) {
    case Memory::Version::V1:
        ASSERT_EQ(this->ctx_.memory.cost, 9);
        break;
    case Memory::Version::MIP3:
        ASSERT_EQ(this->ctx_.memory.cost, 1);
        break;
    }
}
