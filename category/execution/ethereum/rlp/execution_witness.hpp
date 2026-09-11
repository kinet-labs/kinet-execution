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
// along with this program.  If not, see <http://www.apache.org/licenses/>.

#pragma once

#include <category/core/address.hpp>
#include <category/core/byte_string.hpp>
#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/core/result.hpp>

#include <ankerl/unordered_dense.h>

#include <cstdint>
#include <span>

KINET_NAMESPACE_BEGIN

/// A shallowly-parsed witness bundle. Every field is a byte_string_view
/// pointing into the original witness bytes; the caller must keep that
/// buffer alive for as long as this struct is used.
///
/// Wire format (6-field RLP list):
///   [0] block_rlp                     RLP-encoded block
///   [1] nodes                         offset-format node blob (see
///                                     offset_trie.hpp) in a list envelope
///   [2] [code...]                     RLP list of contract bytecodes
///   [3] [header...]                   RLP list of ancestor block headers
///   [4] [address...]                  Parent sender+authority set
///   [5] [address...]                  Grandparent sender+authority set
///
/// Fields [4] and [5] can be left unpopulated for chains/revisions where
/// can_sender_dip_into_reserve is not active (EVM traits, pre-KINET_FOUR).
struct ExecutionWitness
{
    byte_string_view block_rlp;
    byte_string_view encoded_nodes;
    byte_string_view encoded_codes;
    byte_string_view encoded_headers;
    byte_string_view encoded_parent_senders_and_authorities;
    byte_string_view encoded_grandparent_senders_and_authorities;
};

Result<ExecutionWitness>
parse_execution_witness(byte_string_view witness_bytes);

byte_string encode_execution_witness(
    byte_string_view block_rlp, byte_string_view nodes,
    std::span<byte_string const> codes, std::span<byte_string const> headers,
    ankerl::unordered_dense::segmented_set<Address> const
        *const parent_senders_and_authorities = nullptr,
    ankerl::unordered_dense::segmented_set<Address> const
        *const grandparent_senders_and_authorities = nullptr);

KINET_NAMESPACE_END
