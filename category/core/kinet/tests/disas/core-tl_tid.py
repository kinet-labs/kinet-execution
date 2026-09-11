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
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# kinet_core is an OBJECT library, so its .o files are archived into the
# kinet_core_disas STATIC via the PUBLIC kinet_core link dependency.
obj = "libkinet_core_disas.a"
syms = [
    "init_tl_tid",
]
