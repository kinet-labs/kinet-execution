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

#include <features.h>

#include <category/core/mem/huge_mem.hpp>

#include <category/core/assert.h>
#include <category/core/config.hpp>

#include <sys/mman.h>

#if defined(__GNU_LIBRARY__) && __GLIBC__ == 2 && __GLIBC_MINOR__ < 40
    // Before glibc 2.40, <sys/mman.h> did not have the MAP_HUGE_<SIZE> macros;
    // this can be removed when we don't need Ubuntu 24.04 LTS anymore (it has
    // glibc 2.39)
    #include <linux/mman.h>
#endif

#include <cstddef>

KINET_NAMESPACE_BEGIN

namespace
{
    size_t round_up(size_t size, unsigned const bits)
    {
        size_t const mask = (1UL << bits) - 1;
        bool const rem = size & mask;
        size >>= bits;
        size += rem;
        size <<= bits;
        return size;
    }
}

HugeMem::HugeMem(size_t const size)
    : size_{[size] {
        KINET_ASSERT(size > 0);
        return round_up(size, MAP_HUGE_2MB >> MAP_HUGE_SHIFT);
    }()}
    , data_{[this] {
        void *const data = mmap(
            nullptr,
            size_,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_HUGE_2MB,
            -1,
            0);
        KINET_ASSERT(data != MAP_FAILED);
        return static_cast<unsigned char *>(data);
    }()}
{
    /**
     * TODO
     * - mbind (same numa node)
     */

    KINET_ASSERT(!mlock(data_, size_));
}

HugeMem::~HugeMem()
{
    if (size_ > 0) {
        KINET_ASSERT(!munlock(data_, size_));
        KINET_ASSERT(!munmap(data_, size_));
    }
}

KINET_NAMESPACE_END
