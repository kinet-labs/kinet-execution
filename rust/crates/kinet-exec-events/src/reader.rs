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

use kinet_event_ring::{EventDescriptor, EventReader};

use crate::{
    ffi::{
        kinet_c_bytes32, kinet_exec_iter_block_id_prev, kinet_exec_iter_block_number_prev,
        kinet_exec_iter_consensus_prev, kinet_exec_ring_block_id_matches,
        kinet_exec_ring_get_block_number, KINET_EXEC_NONE,
    },
    ExecEventDecoder, ExecEventType,
};

/// Provides utilities for [`ExecEventDecoder`] [`EventDescriptor`]s.
pub trait ExecEventDescriptorExt {
    /// Produces the block number associated with the current [`EventDescriptor`].
    fn get_block_number(&self) -> Option<u64>;

    /// Checks whether the current [`EventDescriptor`] is associated with the provided `block_id`.
    fn block_id_matches(&self, block_id: &kinet_c_bytes32) -> bool;
}

impl<'ring> ExecEventDescriptorExt for EventDescriptor<'ring, ExecEventDecoder> {
    fn get_block_number(&self) -> Option<u64> {
        self.with_raw(kinet_exec_ring_get_block_number)
    }

    fn block_id_matches(&self, block_id: &kinet_c_bytes32) -> bool {
        self.with_raw(|c_event_ring, c_event_descriptor| {
            kinet_exec_ring_block_id_matches(c_event_ring, c_event_descriptor, block_id)
        })
    }
}

/// Provides utilities for [`ExecEventDecoder`] [`EventReader`]s.
pub trait ExecEventReaderExt<'ring> {
    /// Rewinds the [`EventReader`] to the last consensus event specified by the `filter` argument,
    /// producing an [`EventDescriptor`] to it.
    ///
    /// If this method succeeds, the next call to [`EventReader::next_descriptor`] produces the same
    /// event descriptor. Otherwise, the reader remains unchanged.
    fn consensus_prev(
        &mut self,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>>;

    /// Rewinds the [`EventReader`] to the last event in the provided `block_number` specified by
    /// the `filter` argument.
    ///
    /// If this method succeeds, the next call to [`EventReader::next_descriptor`] produces the same
    /// event descriptor. Otherwise, the reader remains unchanged.
    fn block_number_prev(
        &mut self,
        block_number: u64,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>>;

    /// Rewinds the [`EventReader`] to the last event in the provided `block_id` specified by the
    /// `filter` argument.
    ///
    /// If this method succeeds, the next call to [`EventReader::next_descriptor`] produces the same
    /// event descriptor. Otherwise, the reader remains unchanged.
    fn block_id_prev(
        &mut self,
        block_id: &kinet_c_bytes32,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>>;
}

impl<'ring> ExecEventReaderExt<'ring> for EventReader<'ring, ExecEventDecoder> {
    fn consensus_prev(
        &mut self,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>> {
        self.with_raw(|_, c_event_iterator| {
            kinet_exec_iter_consensus_prev(
                c_event_iterator,
                filter.map_or(KINET_EXEC_NONE, ExecEventType::as_c_event_type),
            )
        })
    }

    fn block_number_prev(
        &mut self,
        block_number: u64,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>> {
        self.with_raw(|c_event_ring, c_event_iterator| {
            kinet_exec_iter_block_number_prev(
                c_event_iterator,
                c_event_ring,
                block_number,
                filter.map_or(KINET_EXEC_NONE, ExecEventType::as_c_event_type),
            )
        })
    }

    fn block_id_prev(
        &mut self,
        block_id: &kinet_c_bytes32,
        filter: Option<ExecEventType>,
    ) -> Option<EventDescriptor<'ring, ExecEventDecoder>> {
        self.with_raw(|c_event_ring, c_event_iterator| {
            kinet_exec_iter_block_id_prev(
                c_event_iterator,
                c_event_ring,
                block_id,
                filter.map_or(KINET_EXEC_NONE, ExecEventType::as_c_event_type),
            )
        })
    }
}
