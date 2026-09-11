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

#include <print>

#include <gtest/gtest.h>

#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <unistd.h>

#include <category/core/path_util.h>

TEST(PathUtil, Basic)
{
    int rc;
    int dirfd;
    char pathbuf[PATH_MAX];
    constexpr char const TEST_DIR[] = "/tmp/kinet-path-util-test/xyz";
    constexpr char const PARENT_TEST_DIR[] = "/tmp/kinet-path-util-test";

    rc = kinet_path_open_subdir(
        AT_FDCWD,
        TEST_DIR,
        KINET_PATH_NO_CREATE,
        &dirfd,
        pathbuf,
        sizeof pathbuf);
    ASSERT_EQ(rc, ENOENT); // Can't create the suffix, and it doesn't exist
    ASSERT_EQ(dirfd, -1);

    // Try again, this time we can create it
    rc = kinet_path_open_subdir(
        AT_FDCWD, TEST_DIR, S_IRWXU, &dirfd, pathbuf, sizeof pathbuf);
    ASSERT_EQ(rc, 0);
    ASSERT_NE(dirfd, -1);
    std::println(stderr, "full path is: {}", pathbuf);
    (void)close(dirfd);

    // Try again; we can't create it, but that's OK: it's there now
    rc = kinet_path_open_subdir(
        AT_FDCWD,
        TEST_DIR,
        KINET_PATH_NO_CREATE,
        &dirfd,
        pathbuf,
        sizeof pathbuf);
    ASSERT_EQ(rc, 0);
    ASSERT_NE(dirfd, -1);
    (void)close(dirfd);

    // Remove the test directory
    ASSERT_EQ(rmdir(TEST_DIR), 0);
    ASSERT_EQ(rmdir(PARENT_TEST_DIR), 0);

    // Either parameter can be nullptr
    rc = kinet_path_open_subdir(
        AT_FDCWD,
        TEST_DIR,
        KINET_PATH_NO_CREATE,
        nullptr,
        nullptr,
        sizeof pathbuf);
    ASSERT_EQ(rc, ENOENT);
}
