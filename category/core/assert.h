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

#include <category/core/likely.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

[[noreturn]] void kinet_assertion_failed(
    char const *expr, char const *function, char const *file, long line,
    char const *msg);

#define KINET_ASSERTION_FAILED_WITH_MSG(expr, msg)                             \
    /* Ensure msg is a static string at a fixed address; we do this because */ \
    /* we don't want a fault occurring if dereferencing an unknown pointer */  \
    /* could cause a nested error, e.g., SIGSEGV raised by reading *msg */     \
    /* while we're reporting assertion failure */                              \
    static_assert(__builtin_constant_p(msg));                                  \
    kinet_assertion_failed(                                                    \
        #expr, __extension__ __PRETTY_FUNCTION__, __FILE__, __LINE__, msg);

/// Assert, with backtrace upon failure; accepts an optional message, which
/// must be a compile-time-constant string
#define KINET_ASSERT(expr, ...)                                                \
    if (KINET_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        __VA_OPT__(KINET_ASSERTION_FAILED_WITH_MSG(#expr, __VA_ARGS__);)       \
        __VA_OPT__(__builtin_unreachable();)                                   \
        kinet_assertion_failed(                                                \
            #expr,                                                             \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            nullptr);                                                          \
    }

/// Similar to KINET_ASSERT, but accepts a printf style message; this may not
/// be async signal safe
#define KINET_ASSERT_PRINTF(expr, format, ...)                                 \
    if (KINET_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        char buf[1 << 14]; /* 16 KiB */                                        \
        int written;                                                           \
        char *const buf_end = buf + sizeof(buf);                               \
        char *p = stpcpy(buf, "assertion failure message: ");                  \
        written = snprintf(                                                    \
            p, (size_t)(buf_end - p), (format)__VA_OPT__(, ) __VA_ARGS__);     \
        /* If snprintf fails (written < 0) we're not sure what state buf */    \
        /* is in; write as much as possible so we don't lose info, but */      \
        /* leave room for "\n\0" */                                            \
        p = written < 0 ? buf_end - 2 : p + written;                           \
        if (p < buf_end) {                                                     \
            strncpy(p, "\n", (size_t)(buf_end - p));                           \
        }                                                                      \
        buf_end[-1] = '\0';                                                    \
        kinet_assertion_failed(                                                \
            #expr,                                                             \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            buf);                                                              \
    }

/// Abort with a backtrace; accepts an optional message, which must be a
/// compile-time-constant string
#define KINET_ABORT(...)                                                       \
    __VA_OPT__(KINET_ASSERTION_FAILED_WITH_MSG(nullptr, __VA_ARGS__);)         \
    __VA_OPT__(__builtin_unreachable();)                                       \
    kinet_assertion_failed(                                                    \
        nullptr,                                                               \
        __extension__ __PRETTY_FUNCTION__,                                     \
        __FILE__,                                                              \
        __LINE__,                                                              \
        nullptr);

/// Similar to KINET_ASSERT_PRINTF, but for aborts
#define KINET_ABORT_PRINTF(format, ...)                                        \
    {                                                                          \
        char buf[1 << 14]; /* 16 KiB */                                        \
        int written;                                                           \
        char *const buf_end = buf + sizeof(buf);                               \
        char *p = stpcpy(buf, "abort message: ");                              \
        written = snprintf(                                                    \
            p, (size_t)(buf_end - p), (format)__VA_OPT__(, ) __VA_ARGS__);     \
        /* See comment in KINET_ASSERT_PRINTF */                               \
        p = written < 0 ? buf_end - 2 : p + written;                           \
        if (p < buf_end) {                                                     \
            strncpy(p, "\n", (size_t)(buf_end - p));                           \
        }                                                                      \
        buf_end[-1] = '\0';                                                    \
        kinet_assertion_failed(                                                \
            nullptr,                                                           \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            buf);                                                              \
    }

#if !defined(NDEBUG) || defined(KINET_CORE_FORCE_DEBUG_ASSERT)
    #define KINET_DEBUG_ASSERT(x) KINET_ASSERT(x)
#else
    #define KINET_DEBUG_ASSERT(x)                                              \
        do {                                                                   \
            (void)sizeof(x);                                                   \
        }                                                                      \
        while (0)
#endif

#ifdef __cplusplus
}
#endif
