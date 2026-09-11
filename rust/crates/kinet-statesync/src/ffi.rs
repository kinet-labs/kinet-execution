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

pub use self::bindings::{
    kinet_chain_config, kinet_chain_config_CHAIN_CONFIG_ETHEREUM_MAINNET,
    kinet_chain_config_CHAIN_CONFIG_HIVE_NET, kinet_chain_config_CHAIN_CONFIG_KINET_DEVNET,
    kinet_chain_config_CHAIN_CONFIG_KINET_MAINNET, kinet_chain_config_CHAIN_CONFIG_KINET_TESTNET,
    kinet_statesync_client, kinet_statesync_client_context, kinet_statesync_client_handle_done,
    kinet_statesync_client_handle_target, kinet_statesync_client_handle_upsert, kinet_sync_done,
    kinet_sync_request, kinet_sync_type_SYNC_TYPE_DONE, kinet_sync_type_SYNC_TYPE_REQUEST,
    kinet_sync_type_SYNC_TYPE_TARGET, kinet_sync_type_SYNC_TYPE_UPSERT_ACCOUNT,
    kinet_sync_type_SYNC_TYPE_UPSERT_ACCOUNT_DELETE, kinet_sync_type_SYNC_TYPE_UPSERT_CODE,
    kinet_sync_type_SYNC_TYPE_UPSERT_HEADER, kinet_sync_type_SYNC_TYPE_UPSERT_STORAGE,
    kinet_sync_type_SYNC_TYPE_UPSERT_STORAGE_DELETE,
};

#[allow(dead_code, non_camel_case_types, non_upper_case_globals)]
mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub type StateSyncContext = Box<dyn FnMut(kinet_sync_request)>;

// void (*statesync_send_request)(struct StateSync *, struct SyncRequest)
#[no_mangle]
pub extern "C" fn statesync_send_request(
    statesync: *mut kinet_statesync_client,
    request: kinet_sync_request,
) {
    let statesync = statesync as *mut StateSyncContext;
    unsafe { (*statesync)(request) }
}

fn add_client_prefixes_as_new_peers(ctx: *mut kinet_statesync_client_context, client_version: u32) {
    let prefixes = unsafe { self::bindings::kinet_statesync_client_prefixes() };

    for prefix in 0..prefixes {
        unsafe {
            self::bindings::kinet_statesync_client_handle_new_peer(
                ctx,
                prefix as u64,
                client_version,
            )
        }
    }
}

/// Thin unsafe wrapper around statesync_client_context that handles destruction and finalization
/// checking
pub struct StateSyncCtx {
    chain_config: kinet_chain_config,
    dbname_paths: *const *const ::std::os::raw::c_char,
    len: usize,
    sq_thread_cpu: Option<::std::os::raw::c_uint>,
    request_ctx: StateSyncContext,
    statesync_send_request: ::std::option::Option<
        unsafe extern "C" fn(arg1: *mut kinet_statesync_client, arg2: kinet_sync_request),
    >,
    client_version: u32,

    ctx: Option<*mut kinet_statesync_client_context>,
}

impl StateSyncCtx {
    /// Initialize StateSyncCtx. There should only ever be *one* StateSyncCtx at any given time.
    pub fn new(
        chain_config: kinet_chain_config,
        dbname_paths: *const *const ::std::os::raw::c_char,
        len: usize,
        sq_thread_cpu: Option<::std::os::raw::c_uint>,
        request_ctx: StateSyncContext,
        statesync_send_request: ::std::option::Option<
            unsafe extern "C" fn(arg1: *mut kinet_statesync_client, arg2: kinet_sync_request),
        >,
    ) -> Self {
        let client_version = unsafe { bindings::kinet_statesync_version() };
        assert!(unsafe { bindings::kinet_statesync_client_compatible(client_version) });

        Self {
            chain_config,
            dbname_paths,
            len,
            sq_thread_cpu,
            request_ctx,
            statesync_send_request,
            client_version,

            ctx: None,
        }
    }

    pub fn get_ctx(&self) -> Option<*mut kinet_statesync_client_context> {
        self.ctx
    }

    pub fn get_or_create_ctx(&mut self) -> *mut kinet_statesync_client_context {
        *self.ctx.get_or_insert_with(|| unsafe {
            self::bindings::kinet_statesync_client_context_create(
                self.chain_config,
                self.dbname_paths,
                self.len,
                self.sq_thread_cpu
                    .unwrap_or(self::bindings::KINET_SQPOLL_DISABLED),
                (&mut self.request_ctx as *mut StateSyncContext).cast(),
                self.statesync_send_request,
            )
        })
    }

    pub fn get_or_create_ctx_with_client_prefixes(
        &mut self,
    ) -> *mut kinet_statesync_client_context {
        *self.ctx.get_or_insert_with(|| unsafe {
            let ctx = self::bindings::kinet_statesync_client_context_create(
                self.chain_config,
                self.dbname_paths,
                self.len,
                self.sq_thread_cpu
                    .unwrap_or(self::bindings::KINET_SQPOLL_DISABLED),
                (&mut self.request_ctx as *mut StateSyncContext).cast(),
                self.statesync_send_request,
            );

            add_client_prefixes_as_new_peers(ctx, self.client_version);

            ctx
        })
    }

    pub fn add_client_prefixes_as_new_peers(&mut self) {
        let ctx = self.ctx.expect(
            "add_client_prefixes_as_new_peers should only be called on active StateSyncCtx",
        );

        add_client_prefixes_as_new_peers(ctx, self.client_version);
    }

    pub fn has_reached_target(&mut self) -> bool {
        let ctx = self
            .ctx
            .expect("has_reached_target should only be called on active StateSyncCtx");

        unsafe { self::bindings::kinet_statesync_client_has_reached_target(ctx) }
    }

    // Returns true when the root matches
    pub fn finalize(&mut self) -> bool {
        let ctx = self
            .ctx
            .take()
            .expect("finalize should only be called on active StateSyncCtx");

        let root_matches = unsafe { self::bindings::kinet_statesync_client_finalize(ctx) };

        unsafe {
            self::bindings::kinet_statesync_client_context_destroy(ctx);
        }

        root_matches
    }
}
