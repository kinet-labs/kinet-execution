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

#include <category/core/fiber/fiber_thread_pool.hpp>

#include <category/core/assert.h>
#include <category/core/fiber/config.hpp>
#include <category/core/fiber/fiber_group.hpp>
#include <category/core/fiber/priority_algorithm.hpp>
#include <category/core/fiber/priority_properties.hpp>

#include <boost/fiber/channel_op_status.hpp>
#include <boost/fiber/fiber.hpp>
#include <boost/fiber/operations.hpp>
#include <boost/fiber/protected_fixedsize_stack.hpp>

#include <atomic>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include <pthread.h>

KINET_FIBER_NAMESPACE_BEGIN

FiberThreadPool::FiberThreadPool(
    unsigned const n_threads, bool const prevent_spin)
    : prevent_spin_{prevent_spin}
{
    KINET_ASSERT(n_threads);

    threads_.reserve(n_threads);

    // Create worker threads (1 through n_threads-1) that wait for work via
    // the shared queue with priority-based work-stealing scheduler.
    for (unsigned i = n_threads - 1; i > 0; --i) {
        auto thread = std::thread([this, i] {
            char name[16];
            std::snprintf(name, 16, "ftpool %u", i);
            pthread_setname_np(pthread_self(), name);

            boost::fibers::use_scheduling_algorithm<PriorityAlgorithm>(
                queue_, prevent_spin_);

            std::unique_lock<boost::fibers::mutex> lock{mutex_};
            cv_.wait(lock, [this] { return done_; });
        });
        threads_.push_back(std::move(thread));
    }

    // Thread 0 runs a bootstrap fiber that handles fiber creation requests
    // from FiberGroup constructors.
    auto thread = std::thread([this] {
        pthread_setname_np(pthread_self(), "ftpool 0");

        boost::fibers::use_scheduling_algorithm<PriorityAlgorithm>(
            queue_, prevent_spin_);

        auto *const properties = new PriorityProperties{nullptr};
        boost::fibers::fiber bootstrap_fiber{
            static_cast<boost::fibers::fiber_properties *>(properties),
            std::allocator_arg,
            boost::fibers::protected_fixedsize_stack{
                static_cast<size_t>(8 * 1024 * 1024)},
            [this] {
                std::function<void()> task;
                while (bootstrap_channel_.pop(task) ==
                       boost::fibers::channel_op_status::success) {
                    task();
                }
            }};

        {
            std::unique_lock<boost::fibers::mutex> lock{mutex_};
            cv_.wait(lock, [this] { return done_; });
        }

        bootstrap_fiber.join();
    });
    threads_.push_back(std::move(thread));
}

FiberThreadPool::~FiberThreadPool()
{
    KINET_ASSERT(
        active_groups_.load(std::memory_order_relaxed) == 0,
        "All FiberGroup instances must be destroyed before FiberThreadPool");

    bootstrap_channel_.close();

    {
        std::unique_lock<boost::fibers::mutex> const lock{mutex_};
        done_ = true;
    }

    cv_.notify_all();

    while (threads_.size()) {
        auto &thread = threads_.back();
        thread.join();
        threads_.pop_back();
    }
}

std::unique_ptr<FiberGroup>
FiberThreadPool::create_fiber_group(unsigned const n_fibers)
{
    KINET_ASSERT(n_fibers);
    KINET_ASSERT(
        !done_, "Cannot create FiberGroup after FiberThreadPool shutdown");

    return std::unique_ptr<FiberGroup>(new FiberGroup{*this, n_fibers});
}

KINET_FIBER_NAMESPACE_END
