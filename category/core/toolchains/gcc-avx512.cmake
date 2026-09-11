# Copyright (C) 2025 Kinet Labs, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Apache-2.0 license as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Apache-2.0 license for more details.
#
# You should have received a copy of the Apache-2.0 license
# along with this program.  If not, see <http://www.apache.org/licenses/>.

# This toolchain is good for a basic AVX512 CPU
set(CMAKE_ASM_FLAGS_INIT "-march=skylake-avx512")
set(CMAKE_C_FLAGS_INIT "-march=skylake-avx512")
set(CMAKE_CXX_FLAGS_INIT "-march=skylake-avx512")
