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

#pragma once

#include <category/core/byte_string.hpp>
#include <category/core/bytes.hpp>
#include <category/core/config.hpp>
#include <category/execution/ethereum/core/block.hpp>
#include <category/execution/ethereum/core/transaction.hpp>
#include <category/execution/ethereum/core/withdrawal.hpp>

#include <cstdint>
#include <utility>
#include <vector>

#define EXPLICIT_KINET_CONSENSUS_BLOCK_HEADER(f)                               \
    template decltype(f<KinetConsensusBlockHeaderV0>)                          \
        f<KinetConsensusBlockHeaderV0>;                                        \
    template decltype(f<KinetConsensusBlockHeaderV1>)                          \
        f<KinetConsensusBlockHeaderV1>;                                        \
    template decltype(f<KinetConsensusBlockHeaderV2>)                          \
        f<KinetConsensusBlockHeaderV2>;

KINET_NAMESPACE_BEGIN

struct KinetVoteV0
{
    bytes32_t id{NULL_HASH_BLAKE3};
    uint64_t round{0};
    uint64_t epoch{0};
    bytes32_t parent_id{NULL_HASH_BLAKE3};
    uint64_t parent_round{0};

    friend bool operator==(KinetVoteV0 const &, KinetVoteV0 const &) = default;
};

static_assert(sizeof(KinetVoteV0) == 88);
static_assert(alignof(KinetVoteV0) == 8);

struct KinetVoteV1
{
    bytes32_t id{NULL_HASH_BLAKE3};
    uint64_t round{0};
    uint64_t epoch{0};

    friend bool operator==(KinetVoteV1 const &, KinetVoteV1 const &) = default;
};

static_assert(sizeof(KinetVoteV1) == 48);
static_assert(alignof(KinetVoteV1) == 8);

struct KinetSignerMap
{
    uint32_t num_bits{0};
    byte_string bitmap{};

    friend bool
    operator==(KinetSignerMap const &, KinetSignerMap const &) = default;
};

static_assert(sizeof(KinetSignerMap) == 40);
static_assert(alignof(KinetSignerMap) == 8);

struct KinetSignatures
{
    KinetSignerMap signer_map{};
    byte_string_fixed<96> aggregate_signature{};

    friend bool
    operator==(KinetSignatures const &, KinetSignatures const &) = default;
};

static_assert(sizeof(KinetSignatures) == 136);
static_assert(alignof(KinetSignatures) == 8);

template <typename KinetVote>
struct KinetQuorumCertificate
{
    KinetVote vote{};
    KinetSignatures signatures{};

    friend bool operator==(
        KinetQuorumCertificate const &,
        KinetQuorumCertificate const &) = default;
};

using KinetQuorumCertificateV0 = KinetQuorumCertificate<KinetVoteV0>;
using KinetQuorumCertificateV1 = KinetQuorumCertificate<KinetVoteV1>;

static_assert(sizeof(KinetQuorumCertificateV0) == 224);
static_assert(alignof(KinetQuorumCertificateV0) == 8);

static_assert(sizeof(KinetQuorumCertificateV1) == 184);
static_assert(alignof(KinetQuorumCertificateV1) == 8);

template <class KinetQuorumCertificate>
struct KinetConsensusBlockHeader
{
    uint64_t block_round{0};
    uint64_t epoch{0};
    KinetQuorumCertificate qc{}; // qc is for the previous block
    byte_string_fixed<33> author{};
    uint64_t seqno{0};
    uint128_t timestamp_ns{0};
    byte_string_fixed<96> round_signature{};
    std::vector<BlockHeader> delayed_execution_results{};
    BlockHeader execution_inputs{};
    bytes32_t block_body_id{NULL_HASH_BLAKE3};

    bytes32_t parent_id() const noexcept
    {
        return qc.vote.id;
    }

    friend bool operator==(
        KinetConsensusBlockHeader const &,
        KinetConsensusBlockHeader const &) = default;
};

using KinetConsensusBlockHeaderV0 =
    KinetConsensusBlockHeader<KinetQuorumCertificateV0>;
using KinetConsensusBlockHeaderV1 =
    KinetConsensusBlockHeader<KinetQuorumCertificateV1>;

struct KinetConsensusBlockHeaderV2 : KinetConsensusBlockHeaderV1
{
    uint64_t base_fee{0};
    uint64_t base_fee_trend{0};
    uint64_t base_fee_moment{0};

    friend bool operator==(
        KinetConsensusBlockHeaderV2 const &,
        KinetConsensusBlockHeaderV2 const &) = default;
};

static_assert(sizeof(KinetConsensusBlockHeaderV0) == 1232);
static_assert(alignof(KinetConsensusBlockHeaderV0) == 8);

static_assert(sizeof(KinetConsensusBlockHeaderV1) == 1192);
static_assert(alignof(KinetConsensusBlockHeaderV1) == 8);

static_assert(sizeof(KinetConsensusBlockHeaderV2) == 1216);
static_assert(alignof(KinetConsensusBlockHeaderV2) == 8);

struct KinetConsensusBlockBody
{
    std::vector<Transaction> transactions{};
    std::vector<BlockHeader> ommers{};
    std::vector<Withdrawal> withdrawals{};

    friend bool operator==(
        KinetConsensusBlockBody const &,
        KinetConsensusBlockBody const &) = default;
};

static_assert(sizeof(KinetConsensusBlockBody) == 72);
static_assert(alignof(KinetConsensusBlockBody) == 8);

template <class KinetConsensusBlockHeader>
struct KinetConsensusBlock
{
    KinetConsensusBlockHeader header{};
    KinetConsensusBlockBody body{};

    friend bool operator==(
        KinetConsensusBlock const &, KinetConsensusBlock const &) = default;
};

using KinetConsensusBlockV0 = KinetConsensusBlock<KinetConsensusBlockHeaderV0>;
using KinetConsensusBlockV1 = KinetConsensusBlock<KinetConsensusBlockHeaderV1>;
using KinetConsensusBlockV2 = KinetConsensusBlock<KinetConsensusBlockHeaderV2>;

static_assert(sizeof(KinetConsensusBlockV0) == 1304);
static_assert(alignof(KinetConsensusBlockV0) == 8);

static_assert(sizeof(KinetConsensusBlockV1) == 1264);
static_assert(alignof(KinetConsensusBlockV1) == 8);

static_assert(sizeof(KinetConsensusBlockV2) == 1288);
static_assert(alignof(KinetConsensusBlockV2) == 8);

KINET_NAMESPACE_END
