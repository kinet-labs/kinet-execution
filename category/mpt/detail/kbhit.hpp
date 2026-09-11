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

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

inline bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= tcflag_t(~ICANON);
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);
    return byteswaiting > 0;
}

inline int getch()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= tcflag_t(~ICANON);
    tcsetattr(0, TCSANOW, &term2);

    char ret = 0;
    if (1 == ::read(0, &ret, 1)) {
        tcsetattr(0, TCSANOW, &term);
        return ret;
    }
    tcsetattr(0, TCSANOW, &term);
    return -1;
}

inline char tty_ask_question(char const *const msg, ...)
{
    va_list vl;
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= tcflag_t(~ICANON);
    tcsetattr(0, TCSANOW, &term2);

    std::cout << std::flush;
    va_start(vl, msg);
    vprintf(msg, vl);
    va_end(vl);
    fflush(stdout);

    char buffer[256];
    buffer[0] = -1;
    for (;;) {
        auto const readed = ::read(0, buffer, sizeof(buffer));
        if (readed < 0) {
            std::cerr << "FATAL: Somehow file descriptor 0 (stdin) is not "
                         "readable! Error was: "
                      << strerror(errno) << std::endl;
            abort();
        }
        if (readed > 0) {
            break;
        }
    }
    tcsetattr(0, TCSANOW, &term);

    return buffer[0];
}
