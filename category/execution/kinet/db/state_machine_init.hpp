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

KINET_NAMESPACE_BEGIN

// Populate the mpt::state_machine_kind registry with the page-encoded Kinet
// StateMachine (state_machine_kind::kinet, backed by KinetOnDiskMachine).
// Must run once at process start before any page-encoded mpt::Db is opened
// via the metadata-driven Db(OnDiskDbConfig const &) ctor; otherwise
// create_state_machine() aborts at open time.
//
// Complements register_ethereum_state_machines() (state_machine_kind::
// ethereum). A process that may open either encoding should call both.
//
// Idempotent: re-registering the same kind overwrites the prior factory.
void register_kinet_state_machines();

KINET_NAMESPACE_END
