# Copyright (C) 2025 Category Labs, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.27)

cmake_policy(SET CMP0144 NEW) # find_package uses upper-case _ROOT variables

project(kinet_execution)

# ##############################################################################
# deps
# ##############################################################################

# ##############################################################################
# libs
# ##############################################################################

add_library(
  kinet_execution_ethereum OBJECT
  # ethereum/chain
  "ethereum/chain/chain_config.h"
  "ethereum/chain/chain.hpp"
  "ethereum/chain/ethereum_mainnet.cpp"
  "ethereum/chain/ethereum_mainnet.hpp"
  "ethereum/chain/ethereum_mainnet_alloc.hpp"
  "ethereum/chain/genesis_state.cpp"
  "ethereum/chain/genesis_state.hpp"
  "ethereum/chain/hive_net.cpp"
  "ethereum/chain/hive_net.hpp"
  "ethereum/chain/hive_net_alloc.hpp"
  # ethereum/core
  "ethereum/core/account.hpp"
  "ethereum/core/base_ctypes.h"
  "ethereum/core/block.hpp"
  "ethereum/core/eth_ctypes.h"
  "ethereum/core/contract/abi_decode_error.cpp"
  "ethereum/core/contract/abi_decode_error.hpp"
  "ethereum/core/contract/abi_decode.hpp"
  "ethereum/core/contract/abi_encode.hpp"
  "ethereum/core/contract/abi_signatures.hpp"
  "ethereum/core/contract/big_endian.hpp"
  "ethereum/core/contract/events.hpp"
  "ethereum/core/contract/storage_array.hpp"
  "ethereum/core/contract/storage_variable.hpp"
  "ethereum/core/ecrecover.hpp"
  "ethereum/core/ecrecover/impl.cpp"
  "ethereum/core/ecrecover/impl.hpp"
  "ethereum/core/fmt/account_fmt.hpp"
  "ethereum/core/fmt/address_fmt.hpp"
  "ethereum/core/fmt/block_fmt.hpp"
  "ethereum/core/fmt/bytes_fmt.hpp"
  "ethereum/core/fmt/int_fmt.hpp"
  "ethereum/core/fmt/receipt_fmt.hpp"
  "ethereum/core/fmt/signature_fmt.hpp"
  "ethereum/core/fmt/transaction_fmt.hpp"
  "ethereum/core/fmt/withdrawal_fmt.hpp"
  "ethereum/core/log_level_map.hpp"
  "ethereum/core/receipt.cpp"
  "ethereum/core/receipt.hpp"
  "ethereum/core/rlp/account_rlp.cpp"
  "ethereum/core/rlp/account_rlp.hpp"
  "ethereum/core/rlp/address_rlp.hpp"
  "ethereum/core/rlp/block_rlp.cpp"
  "ethereum/core/rlp/block_rlp.hpp"
  "ethereum/core/rlp/bytes_rlp.hpp"
  "ethereum/core/rlp/int_rlp.hpp"
  "ethereum/core/rlp/receipt_rlp.cpp"
  "ethereum/core/rlp/receipt_rlp.hpp"
  "ethereum/core/rlp/signature_rlp.cpp"
  "ethereum/core/rlp/signature_rlp.hpp"
  "ethereum/core/rlp/transaction_rlp.cpp"
  "ethereum/core/rlp/transaction_rlp.hpp"
  "ethereum/core/rlp/withdrawal_rlp.cpp"
  "ethereum/core/rlp/withdrawal_rlp.hpp"
  "ethereum/core/signature.cpp"
  "ethereum/core/signature.hpp"
  "ethereum/core/transaction.cpp"
  "ethereum/core/transaction.hpp"
  "ethereum/core/units.hpp"
  "ethereum/core/withdrawal.hpp"
  # ethereum/db
  "ethereum/db/block_db.cpp"
  "ethereum/db/block_db.hpp"
  "ethereum/db/commit_builder.cpp"
  "ethereum/db/commit_builder.hpp"
  "ethereum/db/db.hpp"
  "ethereum/db/db_cache.hpp"
  "ethereum/db/db_snapshot.cpp"
  "ethereum/db/db_snapshot.h"
  "ethereum/db/db_snapshot_filesystem.cpp"
  "ethereum/db/db_snapshot_filesystem.h"
  "ethereum/db/file_db.cpp"
  "ethereum/db/file_db.hpp"
  "ethereum/db/offset_trie.hpp"
  "ethereum/db/offset_trie.cpp"
  "ethereum/db/partial_trie_db.hpp"
  "ethereum/db/partial_trie_db.cpp"
  "ethereum/db/state_machine_init.cpp"
  "ethereum/db/state_machine_init.hpp"
  "ethereum/db/storage_key.hpp"
  "ethereum/db/trie_db.cpp"
  "ethereum/db/trie_db.hpp"
  "ethereum/db/trie_rodb.hpp"
  "ethereum/db/util.cpp"
  "ethereum/db/util.hpp"
  # ethereum/event
  "ethereum/event/exec_event_ctypes.h"
  "ethereum/event/exec_event_ctypes_metadata.c"
  "ethereum/event/exec_event_recorder.hpp"
  "ethereum/event/exec_iter_help.h"
  "ethereum/event/record_block_events.cpp"
  "ethereum/event/record_block_events.hpp"
  "ethereum/event/record_consensus_events.cpp"
  "ethereum/event/record_consensus_events.hpp"
  "ethereum/event/record_txn_events.cpp"
  "ethereum/event/record_txn_events.hpp"
  # ethereum/execution
  "ethereum/block_hash_buffer.cpp"
  "ethereum/block_hash_buffer.hpp"
  "ethereum/block_hash_buffer/util.cpp"
  "ethereum/block_hash_buffer/util.hpp"
  "ethereum/block_hash_history.cpp"
  "ethereum/block_hash_history.hpp"
  "ethereum/block_reward.cpp"
  "ethereum/block_reward.hpp"
  "ethereum/create_contract_address.cpp"
  "ethereum/create_contract_address.hpp"
  "ethereum/dispatch_transaction.cpp"
  "ethereum/dispatch_transaction.hpp"
  "ethereum/evmc_host.cpp"
  "ethereum/evmc_host.hpp"
  "ethereum/execute_block.cpp"
  "ethereum/execute_block.hpp"
  "ethereum/execute_block_header.cpp"
  "ethereum/execute_block_header.hpp"
  "ethereum/execute_message.cpp"
  "ethereum/execute_message.hpp"
  "ethereum/execute_transaction.cpp"
  "ethereum/execute_transaction.hpp"
  "ethereum/fmt/event_trace_fmt.hpp"
  "ethereum/process_requests.cpp"
  "ethereum/process_requests.hpp"
  "ethereum/reserve_balance.cpp"
  "ethereum/reserve_balance.hpp"
  "ethereum/trace/call_frame.cpp"
  "ethereum/trace/call_frame.hpp"
  "ethereum/trace/call_tracer.cpp"
  "ethereum/trace/call_tracer.hpp"
  "ethereum/trace/event_trace.cpp"
  "ethereum/trace/event_trace.hpp"
  "ethereum/trace/state_tracer.cpp"
  "ethereum/trace/state_tracer.hpp"
  "ethereum/trace/rlp/call_frame_rlp.cpp"
  "ethereum/trace/rlp/call_frame_rlp.hpp"
  "ethereum/trace/tracer_config.h"
  "ethereum/transaction_gas.cpp"
  "ethereum/transaction_gas.hpp"
  "ethereum/tx_context.cpp"
  "ethereum/tx_context.hpp"
  "ethereum/validate_block.cpp"
  "ethereum/validate_block.hpp"
  "ethereum/validate_transaction.cpp"
  "ethereum/validate_transaction.hpp"
  "ethereum/validate_transaction_error.cpp"
  "ethereum/validate_transaction_error.hpp"
  # ethereum/metrics
  "ethereum/metrics/block_metrics.hpp"
  # ethereum/rlp
  "ethereum/rlp/config.hpp"
  "ethereum/rlp/decode.hpp"
  "ethereum/rlp/encode2.hpp"
  "ethereum/rlp/execution_witness.cpp"
  "ethereum/rlp/execution_witness.hpp"
  # ethereum/state2
  "ethereum/state2/block_state.cpp"
  "ethereum/state2/block_state.hpp"
  "ethereum/state2/fmt/state_deltas_fmt.hpp"
  "ethereum/state2/proposal_post_state.hpp"
  "ethereum/state2/state_deltas.hpp"
  # ethereum/state3
  "ethereum/state3/account_state.cpp"
  "ethereum/state3/account_state.hpp"
  "ethereum/state3/account_substate.hpp"
  "ethereum/state3/page_tracker.hpp"
  "ethereum/state3/state.cpp"
  "ethereum/state3/state.hpp"
  "ethereum/state3/version_stack.hpp"
  # ethereum/test
  "ethereum/test/test_traits_state.hpp"
  # ethereum/types
  "ethereum/types/incarnation.hpp"
  "ethereum/types/fmt/incarnation_fmt.hpp")

add_library(
  kinet_execution_native OBJECT
  # kinet/db
  "kinet/db/commit_block_migration.cpp"
  "kinet/db/commit_block_migration.hpp"
  "kinet/db/page_commit_builder.hpp"
  "kinet/db/page_commit_builder.cpp"
  "kinet/db/state_machine_init.cpp"
  "kinet/db/state_machine_init.hpp"
  "kinet/db/storage_page.cpp"
  "kinet/db/storage_page.hpp"
  # kinet/chain
  "kinet/chain/chain_factory.cpp"
  "kinet/chain/chain_factory.hpp"
  "kinet/chain/kinet_chain.cpp"
  "kinet/chain/kinet_chain.hpp"
  "kinet/chain/kinet_devnet.cpp"
  "kinet/chain/kinet_devnet.hpp"
  "kinet/chain/kinet_devnet_alloc.hpp"
  "kinet/chain/kinet_mainnet.cpp"
  "kinet/chain/kinet_mainnet.hpp"
  "kinet/chain/kinet_mainnet_alloc.hpp"
  "kinet/chain/kinet_testnet.cpp"
  "kinet/chain/kinet_testnet.hpp"
  "kinet/chain/kinet_testnet_alloc.hpp"
  # kinet/core
  "kinet/core/kinet_block.hpp"
  "kinet/core/kinet_ctypes.h"
  "kinet/core/rlp/kinet_block_rlp.cpp"
  "kinet/core/rlp/kinet_block_rlp.hpp"
  # kinet/event
  "kinet/event/record_consensus_events.cpp"
  "kinet/event/record_consensus_events.hpp"
  # kinet/execution
  "kinet/execute_system_transaction.cpp"
  "kinet/execute_system_transaction.hpp"
  "kinet/dispatch_transaction.cpp"
  "kinet/dispatch_transaction.hpp"
  "kinet/min_base_fee.cpp"
  "kinet/min_base_fee.h"
  "kinet/kinet_precompiles.cpp"
  "kinet/kinet_precompiles.hpp"
  "kinet/kinet_precompiles_gas_cost_impl.cpp"
  "kinet/kinet_transaction_gas.cpp"
  "kinet/kinet_transaction_gas.hpp"
  "kinet/reserve_balance.cpp"
  "kinet/reserve_balance.h"
  "kinet/reserve_balance.hpp"
  "kinet/system_sender.hpp"
  "kinet/validate_kinet_block.cpp"
  "kinet/validate_kinet_block.hpp"
  "kinet/validate_kinet_transaction.cpp"
  "kinet/validate_kinet_transaction.hpp"
  "kinet/validate_system_transaction.cpp"
  "kinet/validate_system_transaction.hpp"
  # kinet/reserve_balance
  "kinet/reserve_balance/reserve_balance_contract.cpp"
  "kinet/reserve_balance/reserve_balance_contract.hpp"
  "kinet/reserve_balance/reserve_balance_error.cpp"
  "kinet/reserve_balance/reserve_balance_error.hpp"
  # kinet/staking
  "kinet/staking/config.hpp"
  "kinet/staking/execute_block_prelude.cpp"
  "kinet/staking/execute_block_prelude.hpp"
  "kinet/staking/priority_fee.cpp"
  "kinet/staking/priority_fee.hpp"
  "kinet/staking/fuzzer/staking_contract_machine.cpp"
  "kinet/staking/fuzzer/staking_contract_machine.hpp"
  "kinet/staking/fuzzer/staking_contract_model.cpp"
  "kinet/staking/fuzzer/staking_contract_model.hpp"
  "kinet/staking/read_valset.cpp"
  "kinet/staking/read_valset.hpp"
  "kinet/staking/staking_contract.cpp"
  "kinet/staking/staking_contract.hpp"
  "kinet/staking/test/input_generation.cpp"
  "kinet/staking/test/input_generation.hpp"
  "kinet/staking/util/bls.cpp"
  "kinet/staking/util/bls.hpp"
  "kinet/staking/util/consensus_view.cpp"
  "kinet/staking/util/consensus_view.hpp"
  "kinet/staking/util/constants.cpp"
  "kinet/staking/util/constants.hpp"
  "kinet/staking/util/delegator.cpp"
  "kinet/staking/util/delegator.hpp"
  "kinet/staking/util/secp256k1.cpp"
  "kinet/staking/util/secp256k1.hpp"
  "kinet/staking/util/staking_error.cpp"
  "kinet/staking/util/staking_error.hpp"
  "kinet/staking/util/val_execution.cpp"
  "kinet/staking/util/val_execution.hpp"
  # kinet/state2
  "kinet/state2/proposal_state.hpp")

add_library(
  kinet_execution_runloop OBJECT
  runloop/file_io.hpp
  runloop/file_io.cpp
  runloop/runloop_ethereum.cpp
  runloop/runloop_ethereum.hpp
  runloop/runloop_interface_kinet.cpp
  runloop/runloop_interface_kinet.h
  runloop/runloop_kinet.cpp
  runloop/runloop_kinet.hpp
  runloop/runloop_kinet_ethblocks.cpp
  runloop/runloop_kinet_ethblocks.hpp)

# ##############################################################################
# Precompiles — extracted into a standalone OBJECT library so that the zkvm
# build can reuse it without pulling in the full execution dependency tree.
# ##############################################################################

add_library(
  kinet_precompiles OBJECT
  "ethereum/precompiles.cpp"
  "ethereum/precompiles.hpp"
  "ethereum/precompiles_gas_cost_impl.cpp"
  "ethereum/precompiles_bls12.cpp"
  "ethereum/precompiles_bls12.hpp"
)

target_include_directories(
  kinet_execution_ethereum
  PUBLIC ${CATEGORY_MAIN_DIR}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/test
  PRIVATE ${Boost_INCLUDE_DIRS}
  PUBLIC ${cthash_SOURCE_DIR}/include
  PRIVATE ${silkpre_SOURCE_DIR}/lib)

target_include_directories(
  kinet_execution_native
  PUBLIC ${CATEGORY_MAIN_DIR}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/test
  PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(
  kinet_execution_ethereum PUBLIC KINET_CXX_CTYPES_USE_EVMC_HPP
                                  KINET_CXX_CTYPES_USE_KINET_INTS)

target_compile_definitions(
  kinet_execution_native PUBLIC KINET_CXX_CTYPES_USE_EVMC_HPP
                                KINET_CXX_CTYPES_USE_KINET_INTS)

target_compile_definitions(
  kinet_execution_runloop PUBLIC KINET_CXX_CTYPES_USE_EVMC_HPP
                                 KINET_CXX_CTYPES_USE_INTX)

target_include_directories(
  kinet_precompiles
  PUBLIC ${CATEGORY_MAIN_DIR}
  PUBLIC ${silkpre_SOURCE_DIR}/lib
  PUBLIC ${kinet_crypto_SOURCE_DIR}/src)

target_link_libraries(
  kinet_precompiles
  PUBLIC kinet-vm
  PUBLIC kinet_core
  PUBLIC kinet_crypto
  PUBLIC blst::blst
  PUBLIC c-kzg-4844
  PRIVATE PkgConfig::crypto++
  PUBLIC ethash::keccak
  PUBLIC evmc
  PUBLIC immer
  PUBLIC intx::intx
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC silkpre
  PUBLIC unordered_dense)
kinet_compile_options(kinet_precompiles)

target_link_libraries(
  kinet_execution_ethereum
  PUBLIC kinet-vm
  PUBLIC kinet_core
  PUBLIC kinet_trie
  PUBLIC blst::blst
  PRIVATE Boost::fiber
  PRIVATE Boost::json
  PUBLIC c-kzg-4844
  PRIVATE kinet_crypto
  PRIVATE PkgConfig::brotli
  PRIVATE secp256k1
  PUBLIC evmc
  PUBLIC immer
  PUBLIC intx::intx
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC quill::quill
  PRIVATE silkpre
  PUBLIC unordered_dense
  PUBLIC TBB::tbb)
kinet_compile_options(kinet_execution_ethereum)

target_link_options(kinet_execution_ethereum PRIVATE LINKER:-z,defs)

target_link_libraries(
  kinet_execution_native
  PUBLIC kinet_execution_ethereum
  PUBLIC kinet_core
  PUBLIC kinet_trie
  PUBLIC evmc
  PUBLIC magic_enum::magic_enum
  PUBLIC secp256k1
  PUBLIC quill::quill)
kinet_compile_options(kinet_execution_native)

target_link_libraries(
    kinet_execution_runloop
    PUBLIC kinet_execution_native)
kinet_compile_options(kinet_execution_runloop)

# ##############################################################################
# unit tests
# ##############################################################################
if(NOT CMAKE_CROSSCOMPILING)
  kinet_add_test_folder("ethereum")
  kinet_add_test_folder("kinet")

  add_executable(
      kinet_staking_contract_fuzzer
      "kinet/staking/fuzzer/staking_contract_fuzzer.cpp")
  target_include_directories(
      kinet_staking_contract_fuzzer
      PRIVATE "${CMAKE_BINARY_DIR}/test")
  target_link_libraries(
      kinet_staking_contract_fuzzer
      PRIVATE kinet_execution)
  kinet_compile_options(kinet_staking_contract_fuzzer)
endif()
