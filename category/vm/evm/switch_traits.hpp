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

// NOLINTBEGIN(bugprone-macro-parentheses)

#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.h>

#define SWITCH_EVM_TRAITS(f, ...)                                              \
    switch (rev) {                                                             \
    case KINET_ETH_AMSTERDAM:                                                  \
        return f<::kinet::EvmTraits<KINET_ETH_AMSTERDAM>>(__VA_ARGS__);        \
    case KINET_ETH_OSAKA:                                                      \
        return f<::kinet::EvmTraits<KINET_ETH_OSAKA>>(__VA_ARGS__);            \
    case KINET_ETH_PRAGUE:                                                     \
        return f<::kinet::EvmTraits<KINET_ETH_PRAGUE>>(__VA_ARGS__);           \
    case KINET_ETH_CANCUN:                                                     \
        return f<::kinet::EvmTraits<KINET_ETH_CANCUN>>(__VA_ARGS__);           \
    case KINET_ETH_SHANGHAI:                                                   \
        return f<::kinet::EvmTraits<KINET_ETH_SHANGHAI>>(__VA_ARGS__);         \
    case KINET_ETH_PARIS:                                                      \
        return f<::kinet::EvmTraits<KINET_ETH_PARIS>>(__VA_ARGS__);            \
    case KINET_ETH_LONDON:                                                     \
        return f<::kinet::EvmTraits<KINET_ETH_LONDON>>(__VA_ARGS__);           \
    case KINET_ETH_BERLIN:                                                     \
        return f<::kinet::EvmTraits<KINET_ETH_BERLIN>>(__VA_ARGS__);           \
    default:                                                                   \
        break;                                                                 \
    }

#define SWITCH_KINET_TRAITS(f, ...)                                            \
    switch (rev) {                                                             \
    case KINET_ZERO:                                                           \
        return f<::kinet::KinetTraits<KINET_ZERO>>(__VA_ARGS__);               \
    case KINET_ONE:                                                            \
        return f<::kinet::KinetTraits<KINET_ONE>>(__VA_ARGS__);                \
    case KINET_TWO:                                                            \
        return f<::kinet::KinetTraits<KINET_TWO>>(__VA_ARGS__);                \
    case KINET_THREE:                                                          \
        return f<::kinet::KinetTraits<KINET_THREE>>(__VA_ARGS__);              \
    case KINET_FOUR:                                                           \
        return f<::kinet::KinetTraits<KINET_FOUR>>(__VA_ARGS__);               \
    case KINET_FIVE:                                                           \
        return f<::kinet::KinetTraits<KINET_FIVE>>(__VA_ARGS__);               \
    case KINET_SIX:                                                            \
        return f<::kinet::KinetTraits<KINET_SIX>>(__VA_ARGS__);                \
    case KINET_SEVEN:                                                          \
        return f<::kinet::KinetTraits<KINET_SEVEN>>(__VA_ARGS__);              \
    case KINET_EIGHT:                                                          \
        return f<::kinet::KinetTraits<KINET_EIGHT>>(__VA_ARGS__);              \
    case KINET_NINE:                                                           \
        return f<::kinet::KinetTraits<KINET_NINE>>(__VA_ARGS__);               \
    case KINET_TEN:                                                            \
        return f<::kinet::KinetTraits<KINET_TEN>>(__VA_ARGS__);                \
    case KINET_NEXT:                                                           \
        return f<::kinet::KinetTraits<KINET_NEXT>>(__VA_ARGS__);               \
    }

// NOLINTEND(bugprone-macro-parentheses)
