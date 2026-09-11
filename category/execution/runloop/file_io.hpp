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

#include <category/core/byte_string.hpp>
#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/execution/kinet/core/kinet_block.hpp>

#include <filesystem>

KINET_NAMESPACE_BEGIN

byte_string read_file(bytes32_t const &, std::filesystem::path const &);

KinetConsensusBlockBody
read_body(bytes32_t const &, std::filesystem::path const &);

bytes32_t head_pointer_to_id(std::filesystem::path const &);

KINET_NAMESPACE_END
