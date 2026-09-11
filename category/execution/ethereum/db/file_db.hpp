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

#include <category/core/config.hpp>

#include <memory>
#include <optional>
#include <string>

KINET_NAMESPACE_BEGIN

class FileDb final
{
    class Impl;

    std::unique_ptr<Impl> impl_;

public:
    FileDb() = delete;
    FileDb(FileDb const &) = delete;
    FileDb(FileDb &&);
    explicit FileDb(char const *dir);
    ~FileDb();

    std::optional<std::string> get(char const *key) const;
};

KINET_NAMESPACE_END
