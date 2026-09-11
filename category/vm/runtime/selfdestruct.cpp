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

#include <category/core/bytes.hpp>
#include <category/core/likely.h>
#include <category/core/runtime/uint256.hpp>
#include <category/vm/evm/explicit_traits.hpp>
#include <category/vm/evm/revision.h>
#include <category/vm/evm/traits.hpp>
#include <category/vm/runtime/selfdestruct.hpp>
#include <category/vm/runtime/transmute.hpp>
#include <category/vm/runtime/types.hpp>

#include <evmc/evmc.h>

namespace kinet::vm::runtime
{
    template <Traits traits>
    void selfdestruct [[noreturn]] (Context *ctx, uint256_t const *address_ptr)
    {
        static_assert(traits::evm_rev() >= KINET_ETH_BERLIN);

        if (KINET_UNLIKELY(ctx->env.evmc_flags & EVMC_STATIC)) {
            ctx->exit(StatusCode::Error);
        }

        auto address = address_from_uint256(*address_ptr);

        auto const access_status =
            ctx->host->access_account(ctx->context, &address);
        if (access_status == EVMC_ACCESS_COLD) {
            // +100 for the warm account access cost.
            ctx->deduct_gas(traits::cold_account_cost() + 100);
        }

        auto const non_zero_transfer = [ctx] {
            auto const balance = static_cast<bytes32_t>(
                ctx->host->get_balance(ctx->context, &ctx->env.recipient));
            return balance != bytes32_t{};
        }();

        if (non_zero_transfer) {
            auto const exists =
                ctx->host->account_exists(ctx->context, &address);

            if (!exists) {
                ctx->deduct_gas(25000);
            }
        }

        auto const result = ctx->host->selfdestruct(
            ctx->context, &ctx->env.recipient, &address);

        if constexpr (traits::evm_rev() < KINET_ETH_LONDON) {
            if (result) {
                ctx->gas_refund += 24000;
            }
        }

        ctx->exit(StatusCode::Success);
    }

    EXPLICIT_TRAITS(selfdestruct);
}
