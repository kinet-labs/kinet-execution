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

pub use self::bindings::kinet_executor_pool_config as PoolConfig;
pub(crate) use self::bindings::{
    add_block_override_withdrawal_at, add_override_address, add_override_address_at,
    kinet_block_override_vec, kinet_block_override_vec_create, kinet_block_override_vec_destroy,
    kinet_chain_config, kinet_chain_config_CHAIN_CONFIG_ETHEREUM_MAINNET,
    kinet_chain_config_CHAIN_CONFIG_HIVE_NET, kinet_chain_config_CHAIN_CONFIG_KINET_DEVNET,
    kinet_chain_config_CHAIN_CONFIG_KINET_MAINNET, kinet_chain_config_CHAIN_CONFIG_KINET_TESTNET,
    kinet_executor, kinet_executor_create, kinet_executor_destroy, kinet_executor_eth_call_submit,
    kinet_executor_eth_simulate_submit, kinet_executor_result, kinet_executor_result_release,
    kinet_executor_run_transactions, kinet_state_override_create, kinet_state_override_destroy,
    kinet_state_override_vec, kinet_state_override_vec_create, kinet_state_override_vec_destroy,
    kinet_tracer_config_NOOP_TRACER, set_block_override_base_fee_per_gas_at,
    set_block_override_fee_recipient_at, set_block_override_gas_limit_at,
    set_block_override_number_at, set_block_override_prev_randao_at, set_block_override_time_at,
    set_override_balance, set_override_balance_at, set_override_code, set_override_code_at,
    set_override_nonce, set_override_nonce_at, set_override_state, set_override_state_at,
    set_override_state_diff, set_override_state_diff_at,
};

#[allow(dead_code, non_camel_case_types, non_upper_case_globals)]
mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}
