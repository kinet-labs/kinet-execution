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

pub use self::executor::*;

mod executor;
pub mod ffi;
pub mod overrides;

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub enum ChainId {
    EthereumMainnet,
    KinetMainnet,
    KinetTestnet,
    KinetDevnet,
    HiveNet,
}

impl ChainId {
    fn to_ffi_chain_config(self) -> ffi::kinet_chain_config {
        match self {
            Self::EthereumMainnet => ffi::kinet_chain_config_CHAIN_CONFIG_ETHEREUM_MAINNET,
            Self::KinetMainnet => ffi::kinet_chain_config_CHAIN_CONFIG_KINET_MAINNET,
            Self::KinetTestnet => ffi::kinet_chain_config_CHAIN_CONFIG_KINET_TESTNET,
            Self::KinetDevnet => ffi::kinet_chain_config_CHAIN_CONFIG_KINET_DEVNET,
            Self::HiveNet => ffi::kinet_chain_config_CHAIN_CONFIG_HIVE_NET,
        }
    }
}

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
#[repr(u32)]
pub enum KinetTracer {
    NoopTracer = 0,
    CallTracer,
    PreStateTracer,
    StateDiffTracer,
    AccessListTracer,
}

impl From<KinetTracer> for u32 {
    fn from(tracer: KinetTracer) -> u32 {
        match tracer {
            KinetTracer::NoopTracer => 0,
            KinetTracer::CallTracer => 1,
            KinetTracer::PreStateTracer => 2,
            KinetTracer::StateDiffTracer => 3,
            KinetTracer::AccessListTracer => 4,
        }
    }
}
