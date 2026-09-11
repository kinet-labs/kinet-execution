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

#include <category/core/assert.h>
#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/ethereum/core/receipt.hpp>
#include <category/execution/ethereum/core/transaction.hpp>
#include <category/execution/ethereum/core/withdrawal.hpp>
#include <category/execution/ethereum/db/commit_builder.hpp>
#include <category/execution/ethereum/db/db.hpp>
#include <category/execution/ethereum/trace/call_frame.hpp>
#include <category/execution/ethereum/validate_block.hpp>
#include <category/execution/kinet/db/commit_block_migration.hpp>
#include <category/execution/kinet/db/page_commit_builder.hpp>
#include <category/vm/evm/explicit_traits.hpp>
#include <category/vm/evm/kinet/revision.h>
#include <category/vm/evm/traits.hpp>

KINET_NAMESPACE_BEGIN

template <Traits traits>
    requires is_kinet_trait_v<traits>
void commit_block(
    Db &primary_db, Db *const secondary_db, bytes32_t const &block_id,
    BlockHeader const &header, StateDeltas const &state,
    BlockCommitAncillaries const &anc)
{
    auto add_common_deltas = [&](CommitBuilder &b) {
        b.add_code(anc.code)
            .add_receipts(anc.receipts)
            .add_transactions(anc.transactions, anc.senders)
            .add_call_frames(anc.call_frames)
            .add_ommers(anc.ommers);
        if (anc.withdrawals.has_value()) {
            b.add_withdrawals(anc.withdrawals.value());
        }
    };

    // `canonical_db` is the "source of truth" Db the header populator reads
    // roots from. Both commits call populate_header via this same pointer, so
    // both dbs end up with identical block headers. The pointer is assigned
    // just before the commits run. Non-state roots are the same on both dbs, so
    // the choice only really changes which state_root is stamped into the
    // header.
    Db *canonical_db = nullptr;
    auto populate_header = [&](BlockHeader &h) {
        KINET_ASSERT(canonical_db != nullptr);
        h.receipts_root = canonical_db->receipts_root();
        h.state_root = canonical_db->state_root();
        h.withdrawals_root = canonical_db->withdrawals_root();
        h.transactions_root = canonical_db->transactions_root();
        h.gas_used = anc.receipts.empty() ? 0 : anc.receipts.back().gas_used;
        h.logs_bloom = compute_bloom(anc.receipts);
        h.ommers_hash = compute_ommers_hash(anc.ommers);
    };

    if (secondary_db == nullptr) {
        KINET_ASSERT(primary_db.is_page_encoded() == traits::mip_8_active());
        auto builder = make_commit_builder(header.number, primary_db);
        builder->add_state_deltas(state);
        add_common_deltas(*builder);
        canonical_db = &primary_db;
        primary_db.commit(block_id, *builder, header, state, populate_header);
        return;
    }

    // Dual-write path: one slot db and one page db, in either role order
    // (the offline promote swaps them). The db whose encoding matches the
    // block's revision is canonical; it commits first so its roots are live
    // when the other db's populate_header runs.
    KINET_ASSERT(
        primary_db.is_page_encoded() != secondary_db->is_page_encoded());
    canonical_db = traits::mip_8_active() == primary_db.is_page_encoded()
                       ? &primary_db
                       : secondary_db;
    Db *const other_db =
        canonical_db == &primary_db ? secondary_db : &primary_db;

    auto canonical_builder = make_commit_builder(header.number, *canonical_db);
    canonical_builder->add_state_deltas(state);
    add_common_deltas(*canonical_builder);

    auto other_builder = make_commit_builder(header.number, *other_db);
    other_builder->add_state_deltas(state);
    add_common_deltas(*other_builder);

    canonical_db->commit(
        block_id, *canonical_builder, header, state, populate_header);
    other_db->commit(block_id, *other_builder, header, state, populate_header);
}

EXPLICIT_KINET_TRAITS(commit_block);

KINET_NAMESPACE_END
