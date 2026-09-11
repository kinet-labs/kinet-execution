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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <category/vm/runtime/exit.hpp>
#include <category/vm/runtime/types.hpp>

extern "C" void kinet_vm_runtime_context_out_of_gas_exit
    [[noreturn]] (kinet::vm::runtime::Context *const ctx)
{
    ctx->result.status = kinet::vm::runtime::StatusCode::OutOfGas;
    kinet::vm::runtime::exit(ctx->exit_stack_ptr);
}

namespace kinet::vm::runtime
{
    void Context::stack_unwind [[noreturn]] () noexcept
    {
        is_stack_unwinding_active = true;
        result.status = StatusCode::Error;
        ::kinet::vm::runtime::exit(exit_stack_ptr);
    }

    void Context::exit [[noreturn]] (StatusCode const code) noexcept
    {
        result.status = code;
        ::kinet::vm::runtime::exit(exit_stack_ptr);
    }
}
