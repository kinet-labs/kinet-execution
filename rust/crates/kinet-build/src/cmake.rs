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

#[derive(Debug)]
pub enum KinetCMakeLinkage {
    Static,
    Dynamic,
}

pub struct KinetCMake {
    cmake: cmake::Config,
    linkage: KinetCMakeLinkage,
    with_rpath: bool,

    link_libraries: Vec<&'static str>,
}

impl KinetCMake {
    pub fn new<P>(path: P, linkage: KinetCMakeLinkage) -> Self
    where
        P: AsRef<std::path::Path>,
    {
        let mut cmake = cmake::Config::new(path);

        match linkage {
            KinetCMakeLinkage::Static => {}
            KinetCMakeLinkage::Dynamic => {
                cmake.define("BUILD_SHARED_LIBS", "ON");
            }
        }

        Self {
            cmake,
            linkage,
            with_rpath: false,

            link_libraries: Vec::default(),
        }
    }

    pub fn define<V>(mut self, var: &str, value: V) -> Self
    where
        V: AsRef<std::ffi::OsStr>,
    {
        self.cmake.define(var, value);
        self
    }

    pub fn with_rpath(mut self) -> Self {
        self.with_rpath = true;
        self
    }

    pub fn link_libraries(
        mut self,
        link_libraries: impl IntoIterator<Item = &'static str>,
    ) -> Self {
        self.link_libraries.extend(link_libraries);
        self
    }

    pub fn build(self, target: &'static str) {
        let Self {
            mut cmake,
            linkage,
            with_rpath,

            link_libraries: libraries,
        } = self;

        let dst = cmake.build_target(target).build();

        println!("cargo:rustc-link-search=native={}/build", dst.display());
        println!(
            "cargo:rustc-link-lib={}={}",
            match linkage {
                KinetCMakeLinkage::Static => "static",
                KinetCMakeLinkage::Dynamic => "dylib",
            },
            target
        );
        println!("cargo:CMAKE_BINARY_DIR={}/build", dst.display());

        if with_rpath {
            println!("cargo:rustc-link-arg=-Wl,-rpath,{}/build", dst.display());
        }

        for link_library in libraries {
            println!("cargo:rustc-link-lib={link_library}");
        }
    }
}
