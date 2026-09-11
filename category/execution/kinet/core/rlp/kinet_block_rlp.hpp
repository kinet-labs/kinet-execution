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

#include <category/core/byte_string.hpp>
#include <category/core/result.hpp>
#include <category/core/rlp/config.hpp>
#include <category/execution/kinet/core/kinet_block.hpp>

KINET_RLP_NAMESPACE_BEGIN

Result<uint64_t> decode_consensus_block_header_timestamp_s(byte_string_view &);
Result<KinetConsensusBlockBody> decode_consensus_block_body(byte_string_view &);
template <class KinetConsensusBlockHeader>
Result<KinetConsensusBlockHeader>
decode_consensus_block_header(byte_string_view &);

KINET_RLP_NAMESPACE_END
