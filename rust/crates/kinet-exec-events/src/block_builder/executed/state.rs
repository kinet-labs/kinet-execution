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

use crate::{
    ffi::{
        kinet_c_address, kinet_c_bytes32, kinet_c_eth_txn_header, kinet_c_eth_txn_receipt,
        kinet_exec_block_start,
    },
    ExecutedTxnAccessListEntry, ExecutedTxnCallFrame, ExecutedTxnLog,
    ExecutedTxnSignedAuthorization,
};

#[derive(Debug)]
pub(super) struct BlockReassemblyState {
    pub start: kinet_exec_block_start,
    pub txns: Box<[Option<TxnReassemblyState>]>,
}

#[derive(Debug)]
pub(super) struct TxnReassemblyState {
    pub hash: kinet_c_bytes32,
    pub sender: kinet_c_address,
    pub header: kinet_c_eth_txn_header,
    pub input: Box<[u8]>,
    pub access_list: Vec<ExecutedTxnAccessListEntry>,
    pub authorization_list: Vec<ExecutedTxnSignedAuthorization>,
    pub output: Option<TxnOutputReassemblyState>,
}

#[derive(Debug)]
pub(super) struct TxnOutputReassemblyState {
    pub receipt: kinet_c_eth_txn_receipt,
    pub logs: Box<[Option<ExecutedTxnLog>]>,
    pub call_frames: Option<Box<[Option<ExecutedTxnCallFrame>]>>,
}
