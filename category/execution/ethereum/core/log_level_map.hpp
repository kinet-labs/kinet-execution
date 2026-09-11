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
#include <category/core/log.hpp>

#include <string>
#include <unordered_map>

KINET_NAMESPACE_BEGIN

inline std::unordered_map<std::string, quill::LogLevel> const log_level_map = {
    {"tracel3", quill::LogLevel::TraceL3},
    {"trace_l3", quill::LogLevel::TraceL3},
    {"tracel2", quill::LogLevel::TraceL2},
    {"trace_l2", quill::LogLevel::TraceL2},
    {"tracel1", quill::LogLevel::TraceL1},
    {"trace_l1", quill::LogLevel::TraceL1},
    {"debug", quill::LogLevel::Debug},
    {"info", quill::LogLevel::Info},
    {"warning", quill::LogLevel::Warning},
    {"error", quill::LogLevel::Error},
    {"critical", quill::LogLevel::Critical},
    {"none", quill::LogLevel::None}};

KINET_NAMESPACE_END
