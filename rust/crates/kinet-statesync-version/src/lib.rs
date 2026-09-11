// Copyright (C) 2025-26 Category Labs, Inc.
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

//! The statesync protocol version numbers, generated from execution's
//! `category/statesync/statesync_version.h`. Split out from `kinet-statesync`
//! so that consumers of the constants alone -- kinet-bft's message types --
//! need neither the C++ library nor a libc, and so stay buildable for wasm.

pub use self::bindings::{
    kinet_statesync_protocol_version_KINET_STATESYNC_VERSION as KINET_STATESYNC_VERSION,
    kinet_statesync_protocol_version_KINET_STATESYNC_VERSION_MIN as KINET_STATESYNC_VERSION_MIN,
    kinet_statesync_version_num_KINET_STATESYNC_MAJOR as KINET_STATESYNC_MAJOR,
    kinet_statesync_version_num_KINET_STATESYNC_MINOR_2 as KINET_STATESYNC_MINOR_2,
};

#[allow(dead_code, non_camel_case_types, non_upper_case_globals)]
mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}
