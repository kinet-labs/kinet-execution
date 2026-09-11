// Copyright (C) 2025 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

enum kinet_revision
{
    KINET_ZERO = 0,
    KINET_ONE = 1,
    KINET_TWO = 2,
    KINET_THREE = 3,
    KINET_FOUR = 4,
    KINET_FIVE = 5,
    KINET_SIX = 6,
    KINET_SEVEN = 7,
    KINET_EIGHT = 8,
    KINET_NINE = 9,
    KINET_TEN = 10,
    KINET_NEXT = 11,
};

inline char const *kinet_revision_to_string(enum kinet_revision const rev)
{
    switch (rev) {
    case KINET_ZERO:
        return "KINET_ZERO";
    case KINET_ONE:
        return "KINET_ONE";
    case KINET_TWO:
        return "KINET_TWO";
    case KINET_THREE:
        return "KINET_THREE";
    case KINET_FOUR:
        return "KINET_FOUR";
    case KINET_FIVE:
        return "KINET_FIVE";
    case KINET_SIX:
        return "KINET_SIX";
    case KINET_SEVEN:
        return "KINET_SEVEN";
    case KINET_EIGHT:
        return "KINET_EIGHT";
    case KINET_NINE:
        return "KINET_NINE";
    case KINET_TEN:
        return "KINET_TEN";
    case KINET_NEXT:
        return "KINET_NEXT";
    }
    return ""; // unreachable
}

#ifdef __cplusplus
}
#endif
