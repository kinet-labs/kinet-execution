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

#include <category/core/config.hpp>
#include <category/execution/ethereum/db/util.hpp>
#include <category/execution/kinet/db/state_machine_init.hpp>
#include <category/mpt/state_machine.hpp>
#include <category/mpt/state_machine_kind.hpp>

#include <memory>

KINET_NAMESPACE_BEGIN

void register_kinet_state_machines()
{
    // Only KinetOnDiskMachine participates in metadata-driven open. The
    // in-memory production path keeps the StateMachine&-passing ctor and
    // never reads from disk, so KinetInMemoryMachine is not registered.
    mpt::register_state_machine(mpt::state_machine_kind::kinet, [] {
        return std::unique_ptr<mpt::StateMachine>(new KinetOnDiskMachine{});
    });
}

KINET_NAMESPACE_END
