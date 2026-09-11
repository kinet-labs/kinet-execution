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

use crate::{
    ffi::{self, kinet_event_descriptor, kinet_event_iter_result, kinet_event_iterator_try_next},
    RawEventDescriptor, RawEventReader,
};

/// The result of attempting to retrieve the next event from an [`EventRing`](crate::EventRing).
pub enum EventNextResult<T> {
    /// The next event is available and produced through `T`.
    Ready(T),

    /// The next event is not available.
    NotReady,

    /// The next event was lost due to a gap.
    ///
    /// Receiving this variant is a strong indicator that downstream consumers must switch to a
    /// recovery phase to backfill the data lost from the missing events. You should **not** ignore
    /// this variant unless you are aware of its implications. See
    /// [`EventReader`](crate::EventReader) for more details.
    Gap,
}

impl<'ring> EventNextResult<RawEventDescriptor<'ring>> {
    pub(crate) fn new_from_raw(reader: &mut RawEventReader<'ring>) -> Self {
        let (c_event_iter_result, c_event_descriptor): (
            kinet_event_iter_result,
            kinet_event_descriptor,
        ) = kinet_event_iterator_try_next(&mut reader.inner);

        match c_event_iter_result {
            ffi::KINET_EVENT_SUCCESS => Self::Ready(RawEventDescriptor::new(
                reader.event_ring,
                c_event_descriptor,
            )),
            ffi::KINET_EVENT_NOT_READY => Self::NotReady,
            ffi::KINET_EVENT_GAP => Self::Gap,
            _ => panic!("EventNextResult encountered unknown value {c_event_iter_result}"),
        }
    }

    pub(crate) fn map<T>(
        self,
        f: impl FnOnce(RawEventDescriptor<'ring>) -> T,
    ) -> EventNextResult<T> {
        match self {
            EventNextResult::Ready(descriptor) => EventNextResult::Ready(f(descriptor)),
            EventNextResult::NotReady => EventNextResult::NotReady,
            EventNextResult::Gap => EventNextResult::Gap,
        }
    }
}

/// The result of attempting to read the payload from an
/// [`EventDescriptor`](crate::EventDescriptor).
#[derive(Debug)]
pub enum EventPayloadResult<T> {
    /// The payload was successfully retrieved.
    Ready(T),

    /// The payload's bytes were overwritten while reading them and the result is thus invalid.
    Expired,
}

impl<T> EventPayloadResult<T> {
    /// Maps the event descriptor [`Payload`](EventPayloadResult::Ready) variant to another type
    /// using the provided lambda.
    pub fn map<U>(self, f: impl FnOnce(T) -> U) -> EventPayloadResult<U> {
        match self {
            EventPayloadResult::Ready(payload) => EventPayloadResult::Ready(f(payload)),
            EventPayloadResult::Expired => EventPayloadResult::Expired,
        }
    }
}
