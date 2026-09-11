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

fn main() {
    let mut link_libs = vec!["zstd"];
    if build_rs::input::cargo_cfg_target_os() != "linux" {
        link_libs.push("kinet_event_os_compat");
    }

    println!(
        "cargo:rerun-if-changed={}",
        kinet_build::repository_root().join("category").display()
    );

    kinet_build::KinetCMake::new(
        kinet_build::repository_root().join("category/event"),
        kinet_build::KinetCMakeLinkage::Static,
    )
    .link_libraries(link_libs)
    .build("kinet_event");

    kinet_build::bindgen::KinetBindgen::default()
        .header("wrapper.h")
        .derive_copy()
        .derive_partialeq_eq(None)
        .allowlist_files([
            "category/core/event/event_iterator_inline.h",
            "category/core/event/event_iterator.h",
            "category/core/event/event_metadata.h",
            "category/core/event/event_ring_util.h",
            "category/core/event/event_ring.h",
        ])
        .no_prepend_enum_name()
        .generate_and_build_static("kinet_event__wrap_static_fns");
}
