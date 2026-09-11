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

#include <category/core/cleanup.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

void cleanup_free(char *const *const ptr)
{
    assert(ptr);
    if (*ptr) {
        free(*ptr);
    }
}

void cleanup_close(int *const fd)
{
    assert(fd);
    if (*fd != -1) {
        close(*fd);
        *fd = -1;
    }
}

void cleanup_fclose(FILE *const *const stream)
{
    assert(stream);
    if (*stream) {
        fclose(*stream);
    }
}
