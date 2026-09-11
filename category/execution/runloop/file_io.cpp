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

#include "file_io.hpp"

#include <category/core/assert.h>
#include <category/core/blake3.hpp>
#include <category/core/hex.hpp>
#include <category/execution/ethereum/core/fmt/bytes_fmt.hpp>
#include <category/execution/kinet/core/rlp/kinet_block_rlp.hpp>

#include <fstream>
#include <sstream>

KINET_NAMESPACE_BEGIN

byte_string read_file(bytes32_t const &id, std::filesystem::path const &dir)
{
    std::string const filename = to_hex(id);
    std::filesystem::path const path = dir / filename;
    KINET_ASSERT_PRINTF(
        std::filesystem::exists(path) && std::filesystem::is_regular_file(path),
        "missing or bad file %s",
        path.c_str());
    std::ifstream is(path);
    KINET_ASSERT(is);
    byte_string const data{
        std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()};
    auto const checksum = to_bytes(blake3(data));
    KINET_ASSERT_PRINTF(
        checksum == id, "Checksum failed for file: %s", path.c_str());
    return data;
}

KinetConsensusBlockBody
read_body(bytes32_t const &id, std::filesystem::path const &dir)
{
    auto const data = read_file(id, dir);
    byte_string_view view{data};
    auto const res = rlp::decode_consensus_block_body(view);
    KINET_ASSERT_PRINTF(
        !res.has_error(), "Could not rlp decode body: %s", to_hex(id).c_str());
    return res.value();
}

bytes32_t head_pointer_to_id(std::filesystem::path const &symlink)
{
    char resolved[PATH_MAX] = {};
    auto const r = readlink(symlink.c_str(), resolved, sizeof(resolved));
    if (KINET_UNLIKELY(r == -1)) {
        return bytes32_t{};
    }

    auto const id_string = std::filesystem::path(resolved).stem().string();
    auto const decode_res = from_hex(id_string);
    KINET_ASSERT_PRINTF(
        decode_res.has_value(),
        "Link not hex encoded %s -> %s",
        symlink.c_str(),
        resolved);
    byte_string const hex = decode_res.value();
    return to_bytes(hex);
}

KINET_NAMESPACE_END
