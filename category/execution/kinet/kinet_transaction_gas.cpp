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

#include <category/execution/kinet/min_base_fee.h>
#include <category/execution/kinet/kinet_transaction_gas.hpp>
#include <category/vm/evm/explicit_traits.hpp>

KINET_NAMESPACE_BEGIN

template <Traits traits>
uint64_t compute_gas_refund(
    Transaction const &tx, uint64_t const gas_remaining, uint64_t const refund)
{
    if constexpr (traits::kinet_rev() >= KINET_ONE) {
        return 0;
    }

    return g_star<traits>(tx, gas_remaining, refund);
}

EXPLICIT_KINET_TRAITS(compute_gas_refund);

KINET_NAMESPACE_END
