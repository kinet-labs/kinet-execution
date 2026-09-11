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
#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.h>
#include <evmc/helpers.h>
#include <gtest/gtest.h>

#include <format>
#include <type_traits>
#include <utility>

namespace detail
{
    template <kinet_revision rev>
    using KinetRevisionConstant = std::integral_constant<kinet_revision, rev>;

    template <kinet_eth_revision rev>
    using EvmRevisionConstant = std::integral_constant<kinet_eth_revision, rev>;

    template <std::size_t... Is>
    constexpr auto make_kinet_revision_types(std::index_sequence<Is...>)
    {
        return ::testing::Types<
            KinetRevisionConstant<static_cast<kinet_revision>(Is)>...>{};
    }

    template <std::size_t... Is>
    constexpr auto make_evm_revision_types(std::index_sequence<Is...>)
    {
        return ::testing::Types<
            EvmRevisionConstant<static_cast<kinet_eth_revision>(
                Is + kinet::constants::EARLIEST_SUPPORTED_EVM_FORK)>...>{};
    }

    template <kinet_eth_revision Since, std::size_t... Is>
    constexpr auto make_evm_revision_types_since(std::index_sequence<Is...>)
    {
        constexpr auto filtered = [] {
            std::array<std::size_t, sizeof...(Is)> result{};
            std::size_t count = 0;

            (
                [&] {
                    constexpr auto evm_rev =
                        static_cast<kinet_eth_revision>(Is);
                    if (evm_rev >= Since) {
                        result[count++] = Is;
                    }
                }(),
                ...);

            return std::pair{result, count};
        }();

        return [&]<std::size_t... Js>(std::index_sequence<Js...>) {
            return ::testing::Types<EvmRevisionConstant<
                static_cast<kinet_eth_revision>(filtered.first[Js])>...>{};
        }(std::make_index_sequence<filtered.second>{});
    }

    template <kinet_eth_revision Since, std::size_t... Is>
    constexpr auto make_kinet_revision_types_since(std::index_sequence<Is...>)
    {
        constexpr auto filtered = [] {
            std::array<std::size_t, sizeof...(Is)> result{};
            std::size_t count = 0;

            (
                [&] {
                    constexpr auto kinet_rev = static_cast<kinet_revision>(Is);
                    constexpr auto evm_rev =
                        kinet::KinetTraits<kinet_rev>::evm_rev();
                    if (evm_rev >= Since) {
                        result[count++] = Is;
                    }
                }(),
                ...);

            return std::pair{result, count};
        }();

        // Now expand over the filtered indices
        return [&]<std::size_t... Js>(std::index_sequence<Js...>) {
            return ::testing::Types<KinetRevisionConstant<
                static_cast<kinet_revision>(filtered.first[Js])>...>{};
        }(std::make_index_sequence<filtered.second>{});
    }

    template <kinet_revision Since, std::size_t... Is>
    constexpr auto make_kinet_revision_types_since(std::index_sequence<Is...>)
    {
        constexpr auto filtered = [] {
            std::array<std::size_t, sizeof...(Is)> result{};
            std::size_t count = 0;

            (
                [&] {
                    constexpr auto kinet_rev = static_cast<kinet_revision>(Is);
                    if (kinet_rev >= Since) {
                        result[count++] = Is;
                    }
                }(),
                ...);

            return std::pair{result, count};
        }();

        return [&]<std::size_t... Js>(std::index_sequence<Js...>) {
            return ::testing::Types<KinetRevisionConstant<
                static_cast<kinet_revision>(filtered.first[Js])>...>{};
        }(std::make_index_sequence<filtered.second>{});
    }

    template <kinet_revision Before, std::size_t... Is>
    constexpr auto make_kinet_revision_types_before(std::index_sequence<Is...>)
    {
        constexpr auto filtered = [] {
            std::array<std::size_t, sizeof...(Is)> result{};
            std::size_t count = 0;

            (
                [&] {
                    constexpr auto kinet_rev = static_cast<kinet_revision>(Is);
                    if (kinet_rev < Before) {
                        result[count++] = Is;
                    }
                }(),
                ...);

            return std::pair{result, count};
        }();

        return [&]<std::size_t... Js>(std::index_sequence<Js...>) {
            return ::testing::Types<KinetRevisionConstant<
                static_cast<kinet_revision>(filtered.first[Js])>...>{};
        }(std::make_index_sequence<filtered.second>{});
    }

    using KinetRevisionTypes = decltype(make_kinet_revision_types(
        std::make_index_sequence<KINET_NEXT + 1>{}));

    template <kinet_eth_revision Since>
    using KinetRevisionTypesSinceEvmRevision =
        decltype(make_kinet_revision_types_since<Since>(
            std::make_index_sequence<KINET_NEXT + 1>{}));

    template <kinet_revision Since>
    using KinetRevisionTypesSince =
        decltype(make_kinet_revision_types_since<Since>(
            std::make_index_sequence<KINET_NEXT + 1>{}));

    template <kinet_revision Before>
    using KinetRevisionTypesBefore =
        decltype(make_kinet_revision_types_before<Before>(
            std::make_index_sequence<KINET_NEXT + 1>{}));

    // Skip the unsupported early forks, any fork past LATEST_SUPPORTED_EVM_FORK
    // whose behavior is not yet implemented (e.g. AMSTERDAM), and the
    // KINET_ETH_MAX_REVISION / EXPERIMENTAL sentinel. Generate revisions in the
    // closed range [EARLIEST_SUPPORTED_EVM_FORK, LATEST_SUPPORTED_EVM_FORK].
    // TODO(amsterdam): AMSTERDAM rejoins this matrix automatically once
    // LATEST_SUPPORTED_EVM_FORK is bumped to include it.
    using EvmRevisionTypes = decltype(make_evm_revision_types(
        std::make_index_sequence<
            kinet::constants::LATEST_SUPPORTED_EVM_FORK + 1 -
            kinet::constants::EARLIEST_SUPPORTED_EVM_FORK>{}));

    template <kinet_eth_revision Since>
    using EvmRevisionTypesSince = decltype(make_evm_revision_types_since<Since>(
        std::make_index_sequence<
            kinet::constants::LATEST_SUPPORTED_EVM_FORK + 1>{}));

    // Helper to concatenate two ::testing::Types
    template <typename... Ts>
    struct concat_types;

    template <typename... Ts1, typename... Ts2>
    struct concat_types<::testing::Types<Ts1...>, ::testing::Types<Ts2...>>
    {
        using type = ::testing::Types<Ts1..., Ts2...>;
    };

    template <typename... Ts>
    using concat_types_t = typename concat_types<Ts...>::type;

    // Union of KinetRevisionTypes and EvmRevisionTypes
    using KinetEvmRevisionTypes =
        concat_types_t<KinetRevisionTypes, EvmRevisionTypes>;

    template <kinet_eth_revision Since>
    using KinetEvmRevisionTypesSince = concat_types_t<
        KinetRevisionTypesSinceEvmRevision<Since>,
        EvmRevisionTypesSince<Since>>;

    struct RevisionTestNameGenerator
    {
        template <typename T>
        static std::string GetName(int)
        {
            if constexpr (std::
                              same_as<typename T::value_type, kinet_revision>) {
                return kinet_revision_to_string(T::value);
            }
            else {
                return kinet_eth_revision_to_string(T::value);
            }
        }
    };
}

#define DEFINE_KINET_TRAITS_FIXTURE(FIXTURE_NAME)                              \
    TYPED_TEST_SUITE(                                                          \
        FIXTURE_NAME,                                                          \
        ::detail::KinetRevisionTypes,                                          \
        ::detail::RevisionTestNameGenerator)

#define DEFINE_ETHEREUM_TRAITS_FIXTURE(FIXTURE_NAME)                           \
    TYPED_TEST_SUITE(                                                          \
        FIXTURE_NAME,                                                          \
        ::detail::EvmRevisionTypes,                                            \
        ::detail::RevisionTestNameGenerator)

#define DEFINE_TRAITS_FIXTURE(FIXTURE_NAME)                                    \
    TYPED_TEST_SUITE(                                                          \
        FIXTURE_NAME,                                                          \
        ::detail::KinetEvmRevisionTypes,                                       \
        ::detail::RevisionTestNameGenerator)

template <typename KinetRevisionT>
struct KinetTraitsTest : public ::testing::Test
{
    static constexpr kinet_revision REV = KinetRevisionT::value;
    using Trait = kinet::KinetTraits<REV>;
};

DEFINE_KINET_TRAITS_FIXTURE(KinetTraitsTest);

template <typename EvmRevisionT>
struct EvmTraitsTest : public ::testing::Test
{
    static constexpr kinet_eth_revision REV = EvmRevisionT::value;
    using Trait = kinet::EvmTraits<REV>;
};

DEFINE_ETHEREUM_TRAITS_FIXTURE(EvmTraitsTest);

template <typename T>
struct TraitsTest : public ::testing::Test
{
    static constexpr auto get_trait()
    {
        if constexpr (std::same_as<typename T::value_type, kinet_revision>) {
            return kinet::KinetTraits<T::value>{};
        }
        else {
            return kinet::EvmTraits<T::value>{};
        }
    }

    using Trait = decltype(get_trait());

    static consteval bool is_kinet_trait() noexcept
    {
        return kinet::is_kinet_trait_v<Trait>;
    }

    static consteval bool is_evm_trait() noexcept
    {
        return kinet::is_evm_trait_v<Trait>;
    }
};

DEFINE_TRAITS_FIXTURE(TraitsTest);
