// Copyright (C) 2025-26 Kinet Labs, Inc.
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

fn main() {
    if kinet_build::should_build_execution() {
        let root = kinet_build::repository_root();
        for path in ["CMakeLists.txt", "cmake", "category", "third_party"] {
            println!("cargo:rerun-if-changed={}", root.join(path).display());
        }
        kinet_build::KinetCMake::new(&root, kinet_build::KinetCMakeLinkage::Dynamic)
            .build("kinet_execution");
    }

    kinet_build::bindgen::KinetBindgen::default()
        .header("wrapper.h")
        .derive_copy()
        .allowlist_files(["category/core/log_ffi.h"])
        .generate();
}
