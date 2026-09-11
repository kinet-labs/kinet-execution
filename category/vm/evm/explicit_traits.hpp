// Copyright (C) 2025 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

// NOLINTBEGIN(bugprone-macro-parentheses)

#include <category/core/concat.h>
#include <category/vm/evm/traits.hpp>

#include <evmc/evmc.h>

// Template free functions

#define EXPLICIT_EVM_TRAITS(f)                                                 \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_BERLIN>>)                 \
        f<::kinet::EvmTraits<KINET_ETH_BERLIN>>;                               \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_LONDON>>)                 \
        f<::kinet::EvmTraits<KINET_ETH_LONDON>>;                               \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_PARIS>>)                  \
        f<::kinet::EvmTraits<KINET_ETH_PARIS>>;                                \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_SHANGHAI>>)               \
        f<::kinet::EvmTraits<KINET_ETH_SHANGHAI>>;                             \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_CANCUN>>)                 \
        f<::kinet::EvmTraits<KINET_ETH_CANCUN>>;                               \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_PRAGUE>>)                 \
        f<::kinet::EvmTraits<KINET_ETH_PRAGUE>>;                               \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_OSAKA>>)                  \
        f<::kinet::EvmTraits<KINET_ETH_OSAKA>>;                                \
    template decltype(f<::kinet::EvmTraits<KINET_ETH_AMSTERDAM>>)              \
        f<::kinet::EvmTraits<KINET_ETH_AMSTERDAM>>;

#define EXPLICIT_KINET_TRAITS(f)                                               \
    template decltype(f<::kinet::KinetTraits<KINET_ZERO>>)                     \
        f<::kinet::KinetTraits<KINET_ZERO>>;                                   \
    template decltype(f<::kinet::KinetTraits<KINET_ONE>>)                      \
        f<::kinet::KinetTraits<KINET_ONE>>;                                    \
    template decltype(f<::kinet::KinetTraits<KINET_TWO>>)                      \
        f<::kinet::KinetTraits<KINET_TWO>>;                                    \
    template decltype(f<::kinet::KinetTraits<KINET_THREE>>)                    \
        f<::kinet::KinetTraits<KINET_THREE>>;                                  \
    template decltype(f<::kinet::KinetTraits<KINET_FOUR>>)                     \
        f<::kinet::KinetTraits<KINET_FOUR>>;                                   \
    template decltype(f<::kinet::KinetTraits<KINET_FIVE>>)                     \
        f<::kinet::KinetTraits<KINET_FIVE>>;                                   \
    template decltype(f<::kinet::KinetTraits<KINET_SIX>>)                      \
        f<::kinet::KinetTraits<KINET_SIX>>;                                    \
    template decltype(f<::kinet::KinetTraits<KINET_SEVEN>>)                    \
        f<::kinet::KinetTraits<KINET_SEVEN>>;                                  \
    template decltype(f<::kinet::KinetTraits<KINET_EIGHT>>)                    \
        f<::kinet::KinetTraits<KINET_EIGHT>>;                                  \
    template decltype(f<::kinet::KinetTraits<KINET_NINE>>)                     \
        f<::kinet::KinetTraits<KINET_NINE>>;                                   \
    template decltype(f<::kinet::KinetTraits<KINET_TEN>>)                      \
        f<::kinet::KinetTraits<KINET_TEN>>;                                    \
    template decltype(f<::kinet::KinetTraits<KINET_NEXT>>)                     \
        f<::kinet::KinetTraits<KINET_NEXT>>;

#define EXPLICIT_TRAITS(f)                                                     \
    EXPLICIT_EVM_TRAITS(f)                                                     \
    EXPLICIT_KINET_TRAITS(f)

// Template classes

#define EXPLICIT_EVM_TRAITS_CLASS(c)                                           \
    template class c<::kinet::EvmTraits<KINET_ETH_BERLIN>>;                    \
    template class c<::kinet::EvmTraits<KINET_ETH_LONDON>>;                    \
    template class c<::kinet::EvmTraits<KINET_ETH_PARIS>>;                     \
    template class c<::kinet::EvmTraits<KINET_ETH_SHANGHAI>>;                  \
    template class c<::kinet::EvmTraits<KINET_ETH_CANCUN>>;                    \
    template class c<::kinet::EvmTraits<KINET_ETH_PRAGUE>>;                    \
    template class c<::kinet::EvmTraits<KINET_ETH_OSAKA>>;                     \
    template class c<::kinet::EvmTraits<KINET_ETH_AMSTERDAM>>;

#define EXPLICIT_KINET_TRAITS_CLASS(c)                                         \
    template class c<::kinet::KinetTraits<KINET_ZERO>>;                        \
    template class c<::kinet::KinetTraits<KINET_ONE>>;                         \
    template class c<::kinet::KinetTraits<KINET_TWO>>;                         \
    template class c<::kinet::KinetTraits<KINET_THREE>>;                       \
    template class c<::kinet::KinetTraits<KINET_FOUR>>;                        \
    template class c<::kinet::KinetTraits<KINET_FIVE>>;                        \
    template class c<::kinet::KinetTraits<KINET_SIX>>;                         \
    template class c<::kinet::KinetTraits<KINET_SEVEN>>;                       \
    template class c<::kinet::KinetTraits<KINET_EIGHT>>;                       \
    template class c<::kinet::KinetTraits<KINET_NINE>>;                        \
    template class c<::kinet::KinetTraits<KINET_TEN>>;                         \
    template class c<::kinet::KinetTraits<KINET_NEXT>>;

#define EXPLICIT_TRAITS_CLASS(c)                                               \
    EXPLICIT_EVM_TRAITS_CLASS(c)                                               \
    EXPLICIT_KINET_TRAITS_CLASS(c)

#define EXPLICIT_KINET_TRAITS_STRUCT(c)                                        \
    template struct c<::kinet::KinetTraits<KINET_ZERO>>;                       \
    template struct c<::kinet::KinetTraits<KINET_ONE>>;                        \
    template struct c<::kinet::KinetTraits<KINET_TWO>>;                        \
    template struct c<::kinet::KinetTraits<KINET_THREE>>;                      \
    template struct c<::kinet::KinetTraits<KINET_FOUR>>;                       \
    template struct c<::kinet::KinetTraits<KINET_FIVE>>;                       \
    template struct c<::kinet::KinetTraits<KINET_SIX>>;                        \
    template struct c<::kinet::KinetTraits<KINET_SEVEN>>;                      \
    template struct c<::kinet::KinetTraits<KINET_EIGHT>>;                      \
    template struct c<::kinet::KinetTraits<KINET_NINE>>;                       \
    template struct c<::kinet::KinetTraits<KINET_TEN>>;                        \
    template struct c<::kinet::KinetTraits<KINET_NEXT>>;

// Template member functions
//
// The old approach used a namespace-scope variable template whose initializer
// took &Class::member<traits>. clang-21 rejects this because the initializer
// is access-checked at namespace scope ([temp.spec.general]/6 exempts most
// names in explicit instantiation declarations, but NOT variable template
// initializers).
//
// The new approach explicitly instantiates a helper function template with the
// member pointer as an NTTP. The helper template is declared at namespace
// scope by the macro expansion, and the NTTP appears in the explicit
// instantiation declaration itself (not in a function body or initializer),
// so access checking is relaxed per the standard.

#define EXPLICIT_TRAITS_MEMBER_FN(id)                                          \
    template <auto Ptr>                                                        \
    void id()                                                                  \
    {                                                                          \
        [[gnu::used]] static constexpr auto ptr_ = Ptr;                        \
    }

#define EXPLICIT_EVM_TRAITS_MEMBER_LIST(f, id)                                 \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_BERLIN>>>();              \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_LONDON>>>();              \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_PARIS>>>();               \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_SHANGHAI>>>();            \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_CANCUN>>>();              \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_PRAGUE>>>();              \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_OSAKA>>>();               \
    template void id<&f<::kinet::EvmTraits<KINET_ETH_AMSTERDAM>>>();

#define EXPLICIT_EVM_TRAITS_MEMBER_HELPER(f, id)                               \
    EXPLICIT_TRAITS_MEMBER_FN(id)                                              \
    EXPLICIT_EVM_TRAITS_MEMBER_LIST(f, id)

#define EXPLICIT_EVM_TRAITS_MEMBER(f)                                          \
    EXPLICIT_EVM_TRAITS_MEMBER_HELPER(                                         \
        f, KINET_CORE_CONCAT(_member_fn_ptr_, __COUNTER__))

#define EXPLICIT_KINET_TRAITS_MEMBER_LIST(f, id)                               \
    template void id<&f<::kinet::KinetTraits<KINET_ZERO>>>();                  \
    template void id<&f<::kinet::KinetTraits<KINET_ONE>>>();                   \
    template void id<&f<::kinet::KinetTraits<KINET_TWO>>>();                   \
    template void id<&f<::kinet::KinetTraits<KINET_THREE>>>();                 \
    template void id<&f<::kinet::KinetTraits<KINET_FOUR>>>();                  \
    template void id<&f<::kinet::KinetTraits<KINET_FIVE>>>();                  \
    template void id<&f<::kinet::KinetTraits<KINET_SIX>>>();                   \
    template void id<&f<::kinet::KinetTraits<KINET_SEVEN>>>();                 \
    template void id<&f<::kinet::KinetTraits<KINET_EIGHT>>>();                 \
    template void id<&f<::kinet::KinetTraits<KINET_NINE>>>();                  \
    template void id<&f<::kinet::KinetTraits<KINET_TEN>>>();                   \
    template void id<&f<::kinet::KinetTraits<KINET_NEXT>>>();

#define EXPLICIT_KINET_TRAITS_MEMBER_HELPER(f, id)                             \
    EXPLICIT_TRAITS_MEMBER_FN(id)                                              \
    EXPLICIT_KINET_TRAITS_MEMBER_LIST(f, id)

#define EXPLICIT_KINET_TRAITS_MEMBER(f)                                        \
    EXPLICIT_KINET_TRAITS_MEMBER_HELPER(                                       \
        f, KINET_CORE_CONCAT(_member_fn_ptr_, __COUNTER__))

#define EXPLICIT_TRAITS_MEMBER_HELPER(f, id)                                   \
    EXPLICIT_TRAITS_MEMBER_FN(id)                                              \
    EXPLICIT_EVM_TRAITS_MEMBER_LIST(f, id)                                     \
    EXPLICIT_KINET_TRAITS_MEMBER_LIST(f, id)

#define EXPLICIT_TRAITS_MEMBER(f)                                              \
    EXPLICIT_TRAITS_MEMBER_HELPER(                                             \
        f, KINET_CORE_CONCAT(_member_fn_ptr_, __COUNTER__))

// NOLINTEND(bugprone-macro-parentheses)
