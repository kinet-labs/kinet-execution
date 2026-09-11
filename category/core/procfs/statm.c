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

#include <category/core/cleanup.h> // NOLINT(misc-include-cleaner)
#include <category/core/likely.h>
#include <category/core/procfs/statm.h>

#include <stdbool.h>
#include <stdio.h>

#include <unistd.h>

static long PAGESIZE = 0;

__attribute__((constructor)) static void kinet_procfs_statm_init()
{
    PAGESIZE = sysconf(_SC_PAGESIZE);
}

bool kinet_procfs_self_statm(
    long *const size, long *const resident, long *const shared)
{
    // NOLINTBEGIN(clang-analyzer-unix.Stream)
    FILE *const fp [[gnu::cleanup(cleanup_fclose)]] =
        fopen("/proc/self/statm", "r");
    if (KINET_UNLIKELY(!fp)) {
        return false;
    }

    int const result = fscanf(fp, "%ld %ld %ld", size, resident, shared);
    if (KINET_UNLIKELY(result != 3)) {
        return false;
    }

    return true;
    // NOLINTEND(clang-analyzer-unix.Stream)
}

long kinet_procfs_self_resident()
{
    long size;
    long resident;
    long shared;

    if (KINET_UNLIKELY(!kinet_procfs_self_statm(&size, &resident, &shared))) {
        return -1L;
    }

    return resident * PAGESIZE;
}
