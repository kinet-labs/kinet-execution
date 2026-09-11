// Copyright (C) 2025 Category Labs, Inc.
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

#include <category/async/concepts.hpp>
#include <category/async/config.hpp>
#include <category/async/connected_operation.hpp>
#include <category/async/detail/scope_polyfill.hpp>
#include <category/async/erased_connected_operation.hpp>
#include <category/async/io.hpp>
#include <category/async/io_senders.hpp>
#include <category/async/storage_pool.hpp>
#include <category/core/assert.h>
#include <category/core/io/buffers.hpp>
#include <category/core/io/ring.hpp>

#include <gtest/gtest.h>

#include <category/core/test_util/gtest_signal_stacktrace_printer.hpp> // NOLINT

#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace
{
    TEST(AsyncIODeathTest, read_buffer_exhaustion_causes_death)
    {
        kinet::async::storage_pool pool(
            kinet::async::use_anonymous_inode_tag{});
        kinet::io::Ring testring1;
        kinet::io::Ring testring2(kinet::io::RingConfig{1});
        kinet::io::Buffers testrwbuf = make_buffers_for_segregated_read_write(
            testring1,
            testring2,
            1,
            1,
            kinet::async::AsyncIO::KINET_IO_BUFFERS_READ_SIZE,
            kinet::async::AsyncIO::KINET_IO_BUFFERS_WRITE_SIZE);
        kinet::async::AsyncIO testio(pool, testrwbuf);
        std::vector<kinet::async::read_single_buffer_sender::buffer_type> bufs;
        auto const empty_testio = kinet::make_scope_exit(
            [&]() noexcept { testio.wait_until_done(); });

        struct empty_receiver
        {
            std::vector<kinet::async::read_single_buffer_sender::buffer_type>
                &bufs;

            void set_value(
                kinet::async::erased_connected_operation *,
                kinet::async::read_single_buffer_sender::result_type const r)
            {
                KINET_ASSERT(r);
                // Exactly the same test as the death test, except for this line
                bufs.emplace_back(std::move(r.assume_value().get()));
            }
        };

        auto make = [&] {
            auto state(testio.make_connected(
                kinet::async::read_single_buffer_sender(
                    {0, 0}, kinet::async::DISK_PAGE_SIZE),
                empty_receiver{bufs}));
            state->initiate(); // will reap completions if no buffers free
            (void)state.release();
        };
        for (size_t n = 0; n < 512; n++) {
            make();
        }
        std::cerr << "Must fail after this:" << std::endl;
        make();
    }
}
