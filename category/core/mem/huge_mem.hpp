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

#include <category/core/config.hpp>

#include <cstddef>
#include <new>
#include <utility>

KINET_NAMESPACE_BEGIN

class HugeMem final
{
    size_t size_{0};
    unsigned char *data_{nullptr};

public:
    explicit HugeMem(size_t size);

    HugeMem() = default;

    HugeMem(HugeMem const &) = delete;

    HugeMem(HugeMem &&other) noexcept
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    HugeMem &operator=(HugeMem const &) = delete;

    HugeMem &operator=(HugeMem &&other) noexcept
    {
        if (this != &other) {
            this->~HugeMem();
            new (this) HugeMem(std::move(other));
        }
        return *this;
    }

    ~HugeMem();

    [[gnu::always_inline]] size_t get_size() const
    {
        return size_;
    }

    [[gnu::always_inline]] unsigned char *get_data() const
    {
        return data_;
    }
};

static_assert(sizeof(HugeMem) == 16);
static_assert(alignof(HugeMem) == 8);

KINET_NAMESPACE_END
