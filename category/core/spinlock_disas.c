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

#include <category/core/spinlock.h>

void spinlock_init_disas(spinlock_t *const lock)
{
    spinlock_init(lock);
}

bool spinlock_try_lock_disas(spinlock_t *const lock)
{
    return spinlock_try_lock(lock);
}

void spinlock_lock_disas(spinlock_t *const lock)
{
    spinlock_lock(lock);
}

void spinlock_unlock_disas(spinlock_t *const lock)
{
    spinlock_unlock(lock);
}
