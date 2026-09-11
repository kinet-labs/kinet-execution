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

/**
 * @file
 *
 * Defines the event iterator object and its API; iterators are used for
 * reading events
 */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct kinet_event_descriptor;
struct kinet_event_iterator;
struct kinet_event_ring_control;

// clang-format off

/// Result of trying to atomically read the next available event and advance
/// the iterator past it
enum kinet_event_iter_result
{
    KINET_EVENT_SUCCESS,         ///< Event read and iterator advanced
    KINET_EVENT_NOT_READY,       ///< No events are available right now
    KINET_EVENT_GAP              ///< Sequence number gap detected; not advanced
};

// clang-format on

/// Copy the next event descriptor and advance the iterator, if the next event
/// is available; returns KINET_EVENT_SUCCESS upon success, otherwise returns
/// a code indicating why the iterator could not be advanced
static enum kinet_event_iter_result kinet_event_iterator_try_next(
    struct kinet_event_iterator *, struct kinet_event_descriptor *);

/// Copy the event descriptor at the current iteration point, without advancing
/// the iterator; returns KINET_EVENT_SUCCESS upon success, otherwise returns
/// a code indicating why the descriptor at the iteration point was not ready
static enum kinet_event_iter_result kinet_event_iterator_try_copy(
    struct kinet_event_iterator const *, struct kinet_event_descriptor *);

/// Set the iterator so that the next call to `kinet_event_iterator_try_next`
/// or `kinet_event_iterator_try_copy` will read the event descriptor with the
/// specified sequence number; this performs no checking
static void
kinet_event_iterator_set_seqno(struct kinet_event_iterator *, uint64_t seqno);

/// Reset the iterator to point to the latest event produced; used for gap
/// recovery
static uint64_t kinet_event_iterator_reset(struct kinet_event_iterator *);

// clang-format off

/// Holds the state of a single event iterator
struct kinet_event_iterator
{
    uint64_t read_last_seqno;
    struct kinet_event_descriptor const *descriptors;
    size_t desc_capacity_mask;
    struct kinet_event_ring_control const *control;
};

// clang-format on

#ifdef __cplusplus
} // extern "C"
#endif

#define KINET_EVENT_ITERATOR_INTERNAL
#include "event_iterator_inline.h"
#undef KINET_EVENT_ITERATOR_INTERNAL
