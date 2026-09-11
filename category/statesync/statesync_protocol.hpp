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
#include <category/statesync/statesync_messages.h>

struct kinet_statesync_client_context;

KINET_NAMESPACE_BEGIN

struct StatesyncProtocol
{
    virtual ~StatesyncProtocol() = default;

    virtual void
    send_request(kinet_statesync_client_context *, uint64_t prefix) const = 0;

    virtual bool handle_upsert(
        kinet_statesync_client_context *, kinet_sync_type,
        unsigned char const *, uint64_t) const = 0;
};

struct StatesyncProtocolV1_2 : StatesyncProtocol
{
    virtual void send_request(
        kinet_statesync_client_context *, uint64_t prefix) const override;

    virtual bool handle_upsert(
        kinet_statesync_client_context *, kinet_sync_type,
        unsigned char const *, uint64_t) const override;
};

KINET_NAMESPACE_END
