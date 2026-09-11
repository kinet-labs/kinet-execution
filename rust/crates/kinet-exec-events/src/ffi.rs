// Copyright (C) 2025 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//! This module contains low-level bindings to the kinet execution client event types.

pub use self::bindings::{
    g_kinet_exec_event_metadata, kinet_c_access_list_entry, kinet_c_address,
    kinet_c_auth_list_entry, kinet_c_bytes32, kinet_c_eth_txn_header, kinet_c_eth_txn_receipt,
    kinet_c_uint256_ne, kinet_exec_account_access, kinet_exec_account_access_context,
    kinet_exec_account_access_list_header, kinet_exec_block_end, kinet_exec_block_finalized,
    kinet_exec_block_qc, kinet_exec_block_reject, kinet_exec_block_start, kinet_exec_block_tag,
    kinet_exec_block_verified, kinet_exec_evm_error, kinet_exec_storage_access,
    kinet_exec_txn_access_list_entry, kinet_exec_txn_auth_list_entry, kinet_exec_txn_call_frame,
    kinet_exec_txn_evm_output, kinet_exec_txn_header_start, kinet_exec_txn_log,
    kinet_exec_txn_reject, KINET_EXEC_EVENT_COUNT, KINET_TXN_EIP1559, KINET_TXN_EIP2930,
    KINET_TXN_EIP4844, KINET_TXN_EIP7702, KINET_TXN_LEGACY,
};
pub(crate) use self::bindings::{
    g_kinet_exec_event_schema_hash, kinet_exec_event_type, KINET_EXEC_ACCOUNT_ACCESS,
    KINET_EXEC_ACCOUNT_ACCESS_LIST_HEADER, KINET_EXEC_BLOCK_END, KINET_EXEC_BLOCK_FINALIZED,
    KINET_EXEC_BLOCK_PERF_EVM_ENTER, KINET_EXEC_BLOCK_PERF_EVM_EXIT, KINET_EXEC_BLOCK_QC,
    KINET_EXEC_BLOCK_REJECT, KINET_EXEC_BLOCK_START, KINET_EXEC_BLOCK_VERIFIED,
    KINET_EXEC_EVM_ERROR, KINET_EXEC_NONE, KINET_EXEC_RECORD_ERROR, KINET_EXEC_STORAGE_ACCESS,
    KINET_EXEC_TXN_ACCESS_LIST_ENTRY, KINET_EXEC_TXN_AUTH_LIST_ENTRY, KINET_EXEC_TXN_CALL_FRAME,
    KINET_EXEC_TXN_END, KINET_EXEC_TXN_EVM_OUTPUT, KINET_EXEC_TXN_HEADER_END,
    KINET_EXEC_TXN_HEADER_START, KINET_EXEC_TXN_LOG, KINET_EXEC_TXN_PERF_EVM_ENTER,
    KINET_EXEC_TXN_PERF_EVM_EXIT, KINET_EXEC_TXN_REJECT, KINET_FLOW_ACCOUNT_INDEX,
    KINET_FLOW_BLOCK_SEQNO, KINET_FLOW_TXN_ID,
};

#[allow(
    dead_code,
    missing_docs,
    non_camel_case_types,
    non_upper_case_globals,
    rustdoc::broken_intra_doc_links
)]
mod bindings {
    use ::kinet_event_ring::ffi::{kinet_event_descriptor, kinet_event_iterator, kinet_event_ring};

    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

use ::kinet_event_ring::ffi::{kinet_event_descriptor, kinet_event_iterator, kinet_event_ring};

pub(crate) fn kinet_exec_ring_get_block_number(
    c_event_ring: &kinet_event_ring,
    c_event_descriptor: &kinet_event_descriptor,
) -> Option<u64> {
    let mut block_number = 0;

    let success = unsafe {
        self::bindings::kinet_exec_ring_get_block_number(
            c_event_ring,
            c_event_descriptor,
            &mut block_number,
        )
    };

    success.then_some(block_number)
}

pub(crate) fn kinet_exec_ring_block_id_matches(
    c_event_ring: &kinet_event_ring,
    c_event_descriptor: &kinet_event_descriptor,
    block_id: &kinet_c_bytes32,
) -> bool {
    unsafe {
        self::bindings::kinet_exec_ring_block_id_matches(c_event_ring, c_event_descriptor, block_id)
    }
}

pub(crate) fn kinet_exec_iter_consensus_prev(
    c_event_iterator: &mut kinet_event_iterator,
    c_exec_event_filter: kinet_exec_event_type,
) -> Option<kinet_event_descriptor> {
    let mut c_event_descriptor: kinet_event_descriptor = unsafe { std::mem::zeroed() };

    let success = unsafe {
        self::bindings::kinet_exec_iter_consensus_prev(
            c_event_iterator,
            c_exec_event_filter,
            &mut c_event_descriptor,
        )
    };

    success.then_some(c_event_descriptor)
}

pub(crate) fn kinet_exec_iter_block_number_prev(
    c_event_iterator: &mut kinet_event_iterator,
    c_event_ring: &kinet_event_ring,
    block_number: u64,
    c_exec_event_filter: kinet_exec_event_type,
) -> Option<kinet_event_descriptor> {
    let mut c_event_descriptor: kinet_event_descriptor = unsafe { std::mem::zeroed() };

    let success = unsafe {
        self::bindings::kinet_exec_iter_block_number_prev(
            c_event_iterator,
            c_event_ring,
            block_number,
            c_exec_event_filter,
            &mut c_event_descriptor,
        )
    };

    success.then_some(c_event_descriptor)
}

pub(crate) fn kinet_exec_iter_block_id_prev(
    c_event_iterator: &mut kinet_event_iterator,
    c_event_ring: &kinet_event_ring,
    block_id: &kinet_c_bytes32,
    c_exec_event_filter: kinet_exec_event_type,
) -> Option<kinet_event_descriptor> {
    let mut c_event_descriptor: kinet_event_descriptor = unsafe { std::mem::zeroed() };

    let success = unsafe {
        self::bindings::kinet_exec_iter_block_id_prev(
            c_event_iterator,
            c_event_ring,
            block_id,
            c_exec_event_filter,
            &mut c_event_descriptor,
        )
    };

    success.then_some(c_event_descriptor)
}

/// The default filename that the execution daemon uses when it creates the
/// execution events file.
///
/// This is just the filename, not the full path: the full path is determined
/// by the pathname resolution process followed by
/// [`EventRingPath::resolve`](::kinet_event_ring::EventRingPath::resolve). If
/// a user just wants "the default path" to the live execution events file,
/// they should resolve this filename.
pub const DEFAULT_FILE_NAME: &str = unsafe {
    std::str::from_utf8_unchecked(
        std::ffi::CStr::from_bytes_with_nul_unchecked(
            self::bindings::KINET_EVENT_DEFAULT_EXEC_FILE_NAME,
        )
        .to_bytes(),
    )
};
