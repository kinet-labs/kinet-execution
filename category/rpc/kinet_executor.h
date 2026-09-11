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

#include <category/execution/ethereum/chain/chain_config.h>
#include <category/execution/ethereum/trace/tracer_config.h>
#include <category/rpc/overrides.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

static uint64_t const KINET_ETH_CALL_LOW_GAS_LIMIT = 8'100'000;

struct kinet_executor;

typedef struct kinet_executor_result
{
    int status_code;
    int64_t gas_used;
    int64_t gas_refund;

    uint8_t *output_data;
    size_t output_data_len;

    char *message;

    // for trace (call, prestate, statediff)
    uint8_t *encoded_trace;
    size_t encoded_trace_len;
} kinet_executor_result;

void kinet_executor_result_release(kinet_executor_result *);

struct kinet_executor_pool_config
{
    // Number of threads in the pool.
    unsigned num_threads;

    // Number of fibers per thread.
    unsigned num_fibers;

    // Timeout request if it failed to be scheduled in this time.
    unsigned timeout_sec;

    // Maximum number of requests in the queue. Request is removed from the
    // queue when it starts executing.
    unsigned queue_limit;
};

struct kinet_executor_pool_state
{
    // Number of fibers in the pool.
    unsigned num_fibers;

    // Number of fibers currently executing requests.
    unsigned executing_count;

    // Number of requests in queue.
    unsigned queued_count;

    // Maximum number of requests in the queue.
    unsigned queue_limit;

    // Number of queue full conditions.
    uint64_t queue_full_count;
};

struct kinet_executor_state
{
    struct kinet_executor_pool_state low_gas_pool_state;
    struct kinet_executor_pool_state high_gas_pool_state;
    struct kinet_executor_pool_state trace_block_pool_state;
};

struct kinet_executor *kinet_executor_create(
    struct kinet_executor_pool_config low_pool_conf,
    struct kinet_executor_pool_config high_pool_conf,
    struct kinet_executor_pool_config block_pool_conf,
    unsigned tx_exec_num_fibers, uint64_t node_lru_max_mem, char const *dbpath);

void kinet_executor_destroy(struct kinet_executor *);

void kinet_executor_eth_call_submit(
    struct kinet_executor *, enum kinet_chain_config, uint8_t const *rlp_txn,
    size_t rlp_txn_len, uint8_t const *rlp_header, size_t rlp_header_len,
    uint8_t const *rlp_sender, size_t rlp_sender_len, uint64_t block_number,
    uint8_t const *rlp_block_id, size_t rlp_block_id_len,
    struct kinet_state_override const *,
    void (*complete)(kinet_executor_result *, void *user), void *user,
    enum kinet_tracer_config, bool gas_specified);

struct kinet_executor_state kinet_executor_get_state(struct kinet_executor *);

void kinet_executor_run_transactions(
    struct kinet_executor *, enum kinet_chain_config, uint8_t const *rlp_header,
    size_t rlp_header_len, uint64_t block_number, uint8_t const *rlp_block_id,
    size_t rlp_block_id_len, uint8_t const *rlp_parent_block_id,
    size_t rlp_parent_block_id_len, uint8_t const *rlp_grandparent_block_id,
    size_t rlp_grandparent_block_id_len,
    int64_t transaction_index, /* transaction_index >= 0 implies tracing
                                        of a single transaction. */
    void (*complete)(kinet_executor_result *, void *user), void *user,
    enum kinet_tracer_config);

void kinet_executor_eth_simulate_submit(
    struct kinet_executor *, enum kinet_chain_config,
    uint8_t const *rlp_senders, size_t rlp_senders_len,
    uint8_t const *rlp_calls, size_t rlp_calls_len, uint64_t block_number,
    uint8_t const *rlp_header, size_t rlp_header_len,
    uint8_t const *rlp_block_id, size_t rlp_block_id_len,
    uint8_t const *rlp_grandparent_block_id,
    size_t rlp_grandparent_block_id_len, uint64_t gas_limit, size_t max_calls,
    struct kinet_state_override_vec const *const state_overrides,
    struct kinet_block_override_vec const *const block_overrides,
    bool emit_native_transfer_logs,
    void (*complete)(kinet_executor_result *, void *user), void *user);

#ifdef __cplusplus
}
#endif
