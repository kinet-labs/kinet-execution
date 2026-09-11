# Copyright (C) 2025 Category Labs, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

add_library(kinet-vm-evm OBJECT)

set_target_properties(kinet-vm-evm PROPERTIES LINKER_LANGUAGE CXX)

target_sources(kinet-vm-evm PRIVATE
    "delegation.cpp"
    "delegation.hpp"
    "explicit_traits.hpp"
    "opcodes.hpp"
    "opcodes_xmacro.hpp"
    "revision.cpp"
    "revision.h"
    "status_code.cpp"
    "status_code.h"
    "switch_traits.hpp"
    "traits.hpp"

    # Kinet specifics
    "kinet/revision.h"
)

target_include_directories(kinet-vm-evm
    PUBLIC ${CATEGORY_MAIN_DIR}
)

target_link_libraries(kinet-vm-evm
    PUBLIC evmc::evmc
    PUBLIC kinet_core
)

kinet_compile_options(kinet-vm-evm)

add_library(kinet-vm::kinet-vm-evm ALIAS kinet-vm-evm)
