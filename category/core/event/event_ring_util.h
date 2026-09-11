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

/**
 * @file
 *
 * Defines convenience functions that are useful in most event ring programs,
 * but which are not part of the core API
 */

#include <stddef.h>
#include <stdint.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum kinet_event_content_type : uint16_t;
struct kinet_event_ring;

/// Value passed to kinet_event_resolve_ring_file's `default_path` parameter,
/// to request the hugetlbfs path that is dynamically computed by the
/// kinet_hugetlbfs_open_dir_fd function
constexpr char const *KINET_EVENT_DEFAULT_HUGETLBFS = nullptr;

/// Value passed to the `kinet_event_decompress_snapshot_{fd,mem}` functions
/// to allow unlimited memory allocation during zstd decompression
constexpr size_t KINET_EVENT_NO_MAX_SIZE = 0;

/// Arguments for the `kinet_event_ring_init_simple` function
struct kinet_event_ring_simple_config
{
    uint8_t descriptors_shift;
    uint8_t payload_buf_shift;
    uint16_t context_large_pages;
    enum kinet_event_content_type content_type;
    uint8_t const *schema_hash;
};

/// Output structure returned by `kinet_event_ring_query_flocks`
struct kinet_event_flock_info
{
    int lock; ///< Type of lock held (LOCK_EX or LOCK_SH)
    pid_t pid; ///< Process holding lock
};

/// "All in one" convenience event ring file init for simple cases: given an
/// event ring fd and the required options, calculate the required size of the
/// event ring, call posix_fallocate(2) to ensure the storage is available, then
/// call kinet_event_ring_init_file
int kinet_event_ring_init_simple(
    struct kinet_event_ring_simple_config const *, int ring_fd,
    off_t ring_offset, char const *error_name);

/// Check that the event ring content type and schema hash match the assumed
/// values
int kinet_event_ring_check_content_type(
    struct kinet_event_ring const *, enum kinet_event_content_type,
    uint8_t const *schema_hash);

/// Query information about every process that holds an flock on the file
/// referred to by the given file descriptor; the flock(2) system call is used
/// to detect which processes are writing to an event ring file: exclusive
/// writers place a LOCK_EX lock, shared writers all place LOCK_SH locks
int kinet_event_ring_query_flocks(
    int ring_fd, struct kinet_event_flock_info *, size_t *size);

/// For event ring files that have an exclusive writer, determine the pid of
/// that writer; this is a convenience wrapper around the
/// kinet_event_ring_query_flocks function
int kinet_event_ring_query_excl_writer_pid(int ring_fd, pid_t *pid);

/// Given a path to a file (which does not need to exist), check if the
/// associated file system supports that file being mmap'ed with MAP_HUGETLB
int kinet_check_path_supports_map_hugetlb(char const *path, bool *supported);

/// Open a directory fd, for use in openat(2), to the default subdirectory on
/// a hugetlbfs filesystem that is used to hold event ring files; also computes
/// the full path to this directory; this is a wrapper around the generic API
/// function `kinet_hugetlbfs_open_dir_fd`
int kinet_event_open_hugetlbfs_dir_fd(
    int *dirfd, char *pathbuf, size_t pathbuf_size);

/// Given an event ring file input (typically from the command line), resolve it
/// to a file relative to the directory `default_path` if it does not contain
/// any '/' characters, i.e., if it is a "pure" filename; if it contains a '/'
/// character then copy it as-is, so that it will resolve relative to getcwd(2),
/// similar to how a UNIX shell resolves command names; if `default_path` is
/// KINET_EVENT_DEFAULT_HUGETLBFS, this calls kinet_event_open_hugetlbfs_dir_fd
int kinet_event_resolve_ring_file(
    char const *default_path, char const *file, char *pathbuf,
    size_t pathbuf_size);

/// Check if the given file appears to be an event ring snapshot file
int kinet_event_is_snapshot_file(
    int fd, char const *error_name, bool *is_snapshot);

/// Given a file descriptor to an event ring snapshot file, try to decompress
/// it; if successful, the file descriptor `*fd_out` will will refer to an
/// unlinked temporary file that was created to contain the decompressed
/// contents; this function fails if the resulting decompressed temporary file
/// is larger than `max_size`, use KINET_EVENT_NO_MAX_SIZE to allow any size
int kinet_event_decompress_snapshot_fd(
    int fd_in, size_t max_size, char const *error_name, int *fd_out);

/// Similar to kinet_event_decompress_snapshot_fd, but operates on a memory
/// buffer described by (buf, buf_size) instead of a file descriptor
int kinet_event_decompress_snapshot_mem(
    void const *buf, size_t buf_size, size_t max_size, char const *error_name,
    int *fd_out);

constexpr char KINET_EVENT_DEFAULT_RING_DIR[] = "event-rings";

#ifdef __cplusplus
} // extern "C"
#endif
