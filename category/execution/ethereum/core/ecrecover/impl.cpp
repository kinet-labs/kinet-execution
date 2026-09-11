// Copyright (C) 2025-26 Kinet Labs, Inc.
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

#include <category/crypto/silkpre_vendor/ecdsa.h>
#include <category/execution/ethereum/core/ecrecover/impl.hpp>

#include <secp256k1.h>

#include <memory>

KINET_NAMESPACE_BEGIN

bool recover_address(
    std::span<uint8_t, 20> const out, std::span<uint8_t const, 32> const msg,
    std::span<uint8_t const, 64> const sig, uint8_t const recid)
{

    thread_local std::
        unique_ptr<secp256k1_context, void (*)(secp256k1_context *)> const
            context(
                secp256k1_context_create(KINET_SECP256K1_CONTEXT_FLAGS),
                &secp256k1_context_destroy);

    return kinet_recover_address(
        out.data(), msg.data(), sig.data(), recid, context.get());
}

KINET_NAMESPACE_END
