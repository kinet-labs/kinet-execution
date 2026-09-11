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

use std::marker::PhantomData;

pub(crate) use self::raw::RawEventReader;
use crate::{
    ffi::{
        kinet_event_descriptor, kinet_event_iterator, kinet_event_iterator_reset, kinet_event_ring,
    },
    EventDecoder, EventDescriptor, EventNextResult, RawEventDescriptor,
};

mod raw;

/// Used to consume events from an [`EventRing`](crate::EventRing).
pub struct EventReader<'ring, D>
where
    D: EventDecoder,
{
    pub(crate) raw: RawEventReader<'ring>,
    _phantom: PhantomData<D>,
}

impl<'ring, D> EventReader<'ring, D>
where
    D: EventDecoder,
{
    pub(crate) fn new(raw: RawEventReader<'ring>) -> Self {
        Self {
            raw,
            _phantom: PhantomData,
        }
    }

    pub(crate) fn new_snapshot(mut raw: RawEventReader<'ring>) -> Self {
        raw.inner.read_last_seqno = 0;

        Self {
            raw,
            _phantom: PhantomData,
        }
    }

    /// Produces the next event in the ring.
    pub fn next_descriptor(&mut self) -> EventNextResult<EventDescriptor<'ring, D>> {
        self.raw.next_descriptor().map(EventDescriptor::new)
    }

    /// Resets the reader to the latest event in the ring.
    pub fn reset(&mut self) {
        kinet_event_iterator_reset(&mut self.raw.inner);
    }

    /// Exposes the underlying c-types.
    pub fn with_raw(
        &mut self,
        f: impl FnOnce(&kinet_event_ring, &mut kinet_event_iterator) -> Option<kinet_event_descriptor>,
    ) -> Option<EventDescriptor<'ring, D>> {
        let c_event_descriptor = f(&self.raw.event_ring.inner, &mut self.raw.inner)?;

        let raw_event_descriptor = RawEventDescriptor::new(self.raw.event_ring, c_event_descriptor);

        Some(EventDescriptor::new(raw_event_descriptor))
    }
}
