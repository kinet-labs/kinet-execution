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

#include <category/core/address.hpp>
#include <category/core/assert.h>
#include <category/core/bytes.hpp>
#include <category/core/int.hpp>
#include <category/core/runtime/uint256.hpp>
#include <category/execution/ethereum/core/withdrawal.hpp>
#include <category/rpc/overrides.h>
#include <category/rpc/overrides.hpp>

#include <cstdint>
#include <cstring>
#include <vector>

using namespace kinet;

kinet_state_override *kinet_state_override_create()
{
    kinet_state_override *const m = new kinet_state_override();

    return m;
}

void kinet_state_override_destroy(kinet_state_override *const m)
{
    KINET_ASSERT(m);
    delete m;
}

void add_override_address(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));

    KINET_ASSERT(m->override_sets.find(address) == m->override_sets.end());
    m->override_sets.emplace(
        address, kinet_state_override::kinet_state_override_object{});
}

void set_override_balance(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len, uint8_t const *const balance,
    size_t const balance_len)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    KINET_ASSERT(m->override_sets.find(address) != m->override_sets.end());

    KINET_ASSERT(balance);
    KINET_ASSERT(balance_len == sizeof(uint256_t));
    m->override_sets[address].balance = load_be_unsafe<uint256_t>(balance);
}

void set_override_nonce(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len, uint64_t const nonce)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    KINET_ASSERT(m->override_sets.find(address) != m->override_sets.end());

    m->override_sets[address].nonce = nonce;
}

void set_override_code(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len, uint8_t const *const code, size_t const code_len)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    KINET_ASSERT(m->override_sets.find(address) != m->override_sets.end());

    KINET_ASSERT(code);
    m->override_sets[address].code = {code, code + code_len};
}

void set_override_state_diff(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len, uint8_t const *const key, size_t const key_len,
    uint8_t const *const value, size_t const value_len)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    KINET_ASSERT(m->override_sets.find(address) != m->override_sets.end());

    KINET_ASSERT(key);
    KINET_ASSERT(key_len == sizeof(bytes32_t));
    bytes32_t k;
    std::memcpy(k.bytes, key, sizeof(bytes32_t));

    KINET_ASSERT(value);
    KINET_ASSERT(value_len == sizeof(bytes32_t));
    bytes32_t v;
    std::memcpy(v.bytes, value, sizeof(bytes32_t));

    auto &state_object = m->override_sets[address].state_diff;
    KINET_ASSERT(state_object.find(k) == state_object.end());
    state_object.emplace(k, v);
}

void set_override_state(
    kinet_state_override *const m, uint8_t const *const addr,
    size_t const addr_len, uint8_t const *const key, size_t const key_len,
    uint8_t const *const value, size_t const value_len)
{
    KINET_ASSERT(m);

    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    KINET_ASSERT(m->override_sets.find(address) != m->override_sets.end());

    KINET_ASSERT(key);
    KINET_ASSERT(key_len == sizeof(bytes32_t));
    bytes32_t k;
    std::memcpy(k.bytes, key, sizeof(bytes32_t));

    KINET_ASSERT(value);
    KINET_ASSERT(value_len == sizeof(bytes32_t));
    bytes32_t v;
    std::memcpy(v.bytes, value, sizeof(bytes32_t));

    auto &state_object = m->override_sets[address].state;
    KINET_ASSERT(state_object.find(k) == state_object.end());
    state_object.emplace(k, v);
}

struct kinet_state_override_vec *kinet_state_override_vec_create(size_t size)
{
    auto *const vec = new kinet_state_override_vec(size);
    return vec;
}

void kinet_state_override_vec_destroy(struct kinet_state_override_vec *v)
{
    KINET_ASSERT(v);
    delete[] v->overrides;
    delete v;
}

void add_override_address_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    add_override_address(&v->overrides[index], addr, addr_len);
}

void set_override_balance_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len, uint8_t const *balance, size_t balance_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_override_balance(
        &v->overrides[index], addr, addr_len, balance, balance_len);
}

void set_override_nonce_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len, uint64_t nonce)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_override_nonce(&v->overrides[index], addr, addr_len, nonce);
}

void set_override_code_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len, uint8_t const *code, size_t code_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_override_code(&v->overrides[index], addr, addr_len, code, code_len);
}

void set_override_state_diff_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len, uint8_t const *key, size_t key_len, uint8_t const *value,
    size_t value_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_override_state_diff(
        &v->overrides[index], addr, addr_len, key, key_len, value, value_len);
}

void set_override_state_at(
    struct kinet_state_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len, uint8_t const *key, size_t key_len, uint8_t const *value,
    size_t value_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_override_state(
        &v->overrides[index], addr, addr_len, key, key_len, value, value_len);
}

kinet_block_override *kinet_block_override_create()
{
    return new kinet_block_override();
}

void kinet_block_override_destroy(kinet_block_override *const m)
{
    KINET_ASSERT(m);
    delete m;
}

void set_block_override_number(
    kinet_block_override *const m, uint64_t const number)
{
    KINET_ASSERT(m);
    KINET_ASSERT(!m->number.has_value());
    m->number = number;
}

void set_block_override_time(kinet_block_override *const m, uint64_t const time)
{
    KINET_ASSERT(m);
    KINET_ASSERT(!m->time.has_value());
    m->time = time;
}

void set_block_override_gas_limit(
    kinet_block_override *const m, uint64_t const gas_limit)
{
    KINET_ASSERT(m);
    KINET_ASSERT(!m->gas_limit.has_value());
    m->gas_limit = gas_limit;
}

void set_block_override_fee_recipient(
    kinet_block_override *const m, uint8_t const *const addr,
    size_t const addr_len)
{
    KINET_ASSERT(m);
    KINET_ASSERT(addr);
    KINET_ASSERT(addr_len == sizeof(Address));
    KINET_ASSERT(!m->fee_recipient.has_value());
    Address address;
    std::memcpy(address.bytes, addr, sizeof(Address));
    m->fee_recipient = address;
}

void set_block_override_prev_randao(
    kinet_block_override *const m, uint8_t const *const randao,
    size_t const randao_len)
{
    KINET_ASSERT(m);
    KINET_ASSERT(randao);
    KINET_ASSERT(randao_len == sizeof(bytes32_t));
    KINET_ASSERT(!m->prev_randao.has_value());
    bytes32_t val;
    std::memcpy(val.bytes, randao, sizeof(bytes32_t));
    m->prev_randao = val;
}

void set_block_override_base_fee_per_gas(
    kinet_block_override *const m, uint8_t const *const fee,
    size_t const fee_len)
{
    KINET_ASSERT(m);
    KINET_ASSERT(fee);
    KINET_ASSERT(fee_len == sizeof(uint256_t));
    KINET_ASSERT(!m->base_fee_per_gas.has_value());
    m->base_fee_per_gas = load_be_unsafe<uint256_t>(fee);
}

void add_block_override_withdrawal(
    struct kinet_block_override *const m, uint64_t index,
    uint64_t validator_index, uint64_t amount, uint8_t const *recipient_addr,
    size_t recipient_addr_len)
{
    KINET_ASSERT(m);
    KINET_ASSERT(recipient_addr);
    KINET_ASSERT(recipient_addr_len == sizeof(Address));
    Address recipient;
    std::memcpy(recipient.bytes, recipient_addr, sizeof(Address));

    if (!m->withdrawals.has_value()) {
        m->withdrawals = std::vector<Withdrawal>{};
    }

    m->withdrawals->emplace_back(Withdrawal{
        .index = index,
        .validator_index = validator_index,
        .amount = amount,
        .recipient = recipient,
    });
}

struct kinet_block_override_vec *kinet_block_override_vec_create(size_t size)
{
    auto *const vec = new kinet_block_override_vec(size);
    return vec;
}

void kinet_block_override_vec_destroy(struct kinet_block_override_vec *v)
{
    KINET_ASSERT(v);
    delete[] v->overrides;
    delete v;
}

void set_block_override_number_at(
    struct kinet_block_override_vec *v, size_t index, uint64_t number)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_number(&v->overrides[index], number);
}

void set_block_override_time_at(
    struct kinet_block_override_vec *v, size_t index, uint64_t time)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_time(&v->overrides[index], time);
}

void set_block_override_gas_limit_at(
    struct kinet_block_override_vec *v, size_t index, uint64_t gas_limit)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_gas_limit(&v->overrides[index], gas_limit);
}

void set_block_override_fee_recipient_at(
    struct kinet_block_override_vec *v, size_t index, uint8_t const *addr,
    size_t addr_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_fee_recipient(&v->overrides[index], addr, addr_len);
}

void set_block_override_prev_randao_at(
    struct kinet_block_override_vec *v, size_t index, uint8_t const *randao,
    size_t randao_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_prev_randao(&v->overrides[index], randao, randao_len);
}

void set_block_override_base_fee_per_gas_at(
    struct kinet_block_override_vec *v, size_t index, uint8_t const *fee,
    size_t fee_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    set_block_override_base_fee_per_gas(&v->overrides[index], fee, fee_len);
}

void add_block_override_withdrawal_at(
    struct kinet_block_override_vec *v, size_t index, uint64_t withdrawal_index,
    uint64_t validator_index, uint64_t amount, uint8_t const *recipient_addr,
    size_t recipient_addr_len)
{
    KINET_ASSERT(v);
    KINET_ASSERT(index < v->size);
    add_block_override_withdrawal(
        &v->overrides[index],
        withdrawal_index,
        validator_index,
        amount,
        recipient_addr,
        recipient_addr_len);
}
