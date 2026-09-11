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

#include <category/core/config.hpp>
#include <category/execution/kinet/core/kinet_block.hpp>

#include <category/core/bytes.hpp>

#include <filesystem>
#include <fstream>
#include <optional>

KINET_NAMESPACE_BEGIN

struct KinetChain;

enum class WalAction : uint8_t
{
    PROPOSE = 0,
    FINALIZE = 1,
};

static_assert(sizeof(WalAction) == 1);
static_assert(alignof(WalAction) == 1);

struct WalEntry
{
    WalAction action;
    kinet::bytes32_t id;
};

static_assert(sizeof(WalEntry) == 33);
static_assert(alignof(WalEntry) == 1);

class WalReader
{
    KinetChain const &chain_;
    std::ifstream cursor_;
    std::filesystem::path ledger_dir_;

public:
    struct Result
    {
        WalAction action;
        KinetConsensusBlockHeader header;
        KinetConsensusBlockBody body;
    };

    WalReader(KinetChain const &, std::filesystem::path const &ledger_dir);

    std::optional<Result> next();

    bool rewind_to(WalEntry const &);
};

KINET_NAMESPACE_END
