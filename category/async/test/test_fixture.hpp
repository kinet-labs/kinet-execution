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

#include "gtest/gtest.h"

#include <category/async/io.hpp>

#include <category/core/small_prng.hpp>
#include <category/core/test_util/gtest_signal_stacktrace_printer.hpp> // NOLINT

namespace kinet::test
{
    template <class Base>
    struct AsyncTestFixture : public Base
    {
        static constexpr size_t TEST_FILE_SIZE = 1024 * 1024;
        static constexpr size_t MAX_CONCURRENCY = 4;

        struct shared_state_t
        {
            static kinet::io::Ring make_ring()
            {
                return kinet::io::Ring({MAX_CONCURRENCY, 0});
            }

            static kinet::io::Buffers make_buffers(kinet::io::Ring &ring)
            {
                return kinet::io::make_buffers_for_read_only(
                    ring, MAX_CONCURRENCY, 1UL << 13);
            }

            std::vector<std::byte> const testfilecontents = [] {
                std::vector<std::byte> ret(TEST_FILE_SIZE);
                std::span<
                    kinet::small_prng::value_type,
                    TEST_FILE_SIZE / sizeof(kinet::small_prng::value_type)>
                    s((kinet::small_prng::value_type *)ret.data(),
                      TEST_FILE_SIZE / sizeof(kinet::small_prng::value_type));
                kinet::small_prng rand;
                for (auto &i : s) {
                    i = rand();
                }
                return ret;
            }();
            kinet::async::storage_pool pool{
                kinet::async::use_anonymous_inode_tag{}};
            kinet::io::Ring testring = make_ring();
            kinet::io::Buffers testrwbuf = make_buffers(testring);
            std::unique_ptr<kinet::async::AsyncIO> testio = [this] {
                auto ret =
                    std::make_unique<kinet::async::AsyncIO>(pool, testrwbuf);
                auto const fd = pool.chunk(kinet::async::storage_pool::seq, 0)
                                    .write_fd(TEST_FILE_SIZE);
                KINET_ASSERT(
                    TEST_FILE_SIZE == ::pwrite(
                                          fd.first,
                                          testfilecontents.data(),
                                          TEST_FILE_SIZE,
                                          static_cast<off_t>(fd.second)));
                return ret;
            }();
            kinet::small_prng test_rand;
        };

    protected:
        static std::unique_ptr<shared_state_t> &shared_state_()
        {
            static std::unique_ptr<shared_state_t> v;
            return v;
        }

        static void SetUpTestSuite()
        {
            shared_state_() = std::make_unique<shared_state_t>();
        }

        static void TearDownTestSuite()
        {
            shared_state_().reset();
        }
    };
}
