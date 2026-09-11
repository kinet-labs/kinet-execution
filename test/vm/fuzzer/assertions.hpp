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

#include <category/execution/ethereum/state3/account_state.hpp>
#include <category/execution/ethereum/state3/state.hpp>

#include <evmc/evmc.hpp>

namespace kinet::vm::fuzzing
{
    void assert_equal(
        AccountState::StorageMap const &a, AccountState::StorageMap const &b);

    void assert_equal(
        Address const &k, State &a, AccountState const &as, State &b,
        AccountState const &bs);

    void assert_equal(State &, State &);

    void assert_equal(
        evmc::Result const &spec_result, evmc::Result const &compiler_result,
        bool strict_out_of_gas);
}
