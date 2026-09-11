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

#include <category/vm/evm/opcodes.hpp>
#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.hpp>

#include <array>
#include <cstdint>

namespace kinet::vm::runtime
{
    struct StoreCost
    {
        int64_t gas_cost;
        int64_t gas_refund;
    };

    template <Traits traits>
    struct StorageCostTable
    {
        static constexpr std::array<StoreCost, 9> costs{};
    };

    template <Traits traits>
    static consteval int64_t minimum_store_gas()
    {
        constexpr auto costs = StorageCostTable<traits>::costs;
        constexpr auto min_gas =
            std::min_element(costs.begin(), costs.end(), [](auto ca, auto cb) {
                return ca.gas_cost < cb.gas_cost;
            })->gas_cost;
        static_assert(
            compiler::opcode_table<traits>[compiler::SSTORE].min_gas ==
            min_gas);
        return min_gas;
    }

    template <Traits traits>
    constexpr StoreCost store_cost(evmc_storage_status const status)
    {
        return StorageCostTable<traits>::costs[status];
    }

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_BERLIN>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 15000},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -15000},
            StoreCost{.gas_cost = 100, .gas_refund = 15000},
            StoreCost{.gas_cost = 100, .gas_refund = -12200},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_LONDON>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_PARIS>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_SHANGHAI>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_CANCUN>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_PRAGUE>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_OSAKA>>
    {
        static constexpr auto costs = std::array{
            StoreCost{.gas_cost = 100, .gas_refund = 0},
            StoreCost{.gas_cost = 20000, .gas_refund = 0},
            StoreCost{.gas_cost = 2900, .gas_refund = 4800},
            StoreCost{.gas_cost = 2900, .gas_refund = 0},
            StoreCost{.gas_cost = 100, .gas_refund = -4800},
            StoreCost{.gas_cost = 100, .gas_refund = 4800},
            StoreCost{.gas_cost = 100, .gas_refund = -2000},
            StoreCost{.gas_cost = 100, .gas_refund = 19900},
            StoreCost{.gas_cost = 100, .gas_refund = 2800},
        };
    };

    template <>
    struct StorageCostTable<EvmTraits<KINET_ETH_AMSTERDAM>>
        : StorageCostTable<EvmTraits<KINET_ETH_OSAKA>>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_ZERO>>
        : StorageCostTable<KinetTraits<KINET_ZERO>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_ONE>>
        : StorageCostTable<KinetTraits<KINET_ONE>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_TWO>>
        : StorageCostTable<KinetTraits<KINET_TWO>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_THREE>>
        : StorageCostTable<KinetTraits<KINET_THREE>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_FOUR>>
        : StorageCostTable<KinetTraits<KINET_FOUR>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_FIVE>>
        : StorageCostTable<KinetTraits<KINET_FIVE>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_SIX>>
        : StorageCostTable<KinetTraits<KINET_SIX>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_SEVEN>>
        : StorageCostTable<KinetTraits<KINET_SEVEN>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_EIGHT>>
        : StorageCostTable<KinetTraits<KINET_EIGHT>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_NINE>>
        : StorageCostTable<KinetTraits<KINET_NINE>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_TEN>>
        : StorageCostTable<KinetTraits<KINET_TEN>::evm_base>
    {
    };

    template <>
    struct StorageCostTable<KinetTraits<KINET_NEXT>>
        : StorageCostTable<KinetTraits<KINET_NEXT>::evm_base>
    {
    };
}
