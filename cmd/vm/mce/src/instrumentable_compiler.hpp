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

#include <instrumentation_device.hpp>
#include <stopwatch.hpp>

#include <category/core/assert.h>
#include <category/core/log.hpp>
#include <category/vm/compiler/ir/basic_blocks.hpp>
#include <category/vm/compiler/ir/x86.hpp>
#include <category/vm/evm/traits.hpp>

#include <asmjit/x86.h>
#include <evmc/evmc.h>
#include <valgrind/cachegrind.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>

struct CompilerBinary
{
    std::shared_ptr<kinet::vm::compiler::native::Nativecode> ncode;
};

using Binary = CompilerBinary;

template <bool instrument>
class InstrumentableCompiler
{
public:
    InstrumentableCompiler(
        asmjit::JitRuntime &rt,
        kinet::vm::compiler::native::CompilerConfig const &config)
        : rt_(rt)
        , config_(config)
    {
    }

    template <kinet::Traits traits>
    Binary compile(
        kinet::vm::compiler::basic_blocks::BasicBlocksIR const &ir,
        InstrumentationDevice const device)
    {
        switch (device) {
        case InstrumentationDevice::Cachegrind:
            return compile<traits, InstrumentationDevice::Cachegrind>(ir);
        case InstrumentationDevice::WallClock:
            return compile<traits, InstrumentationDevice::WallClock>(ir);
        }
        std::unreachable();
    }

    template <kinet::Traits traits, InstrumentationDevice device>
    Binary compile(kinet::vm::compiler::basic_blocks::BasicBlocksIR const &ir)
    {
        if constexpr (instrument) {
            if constexpr (device == InstrumentationDevice::Cachegrind) {
                CACHEGRIND_START_INSTRUMENTATION;
                auto ans = dispatch_compile<traits>(ir);
                CACHEGRIND_STOP_INSTRUMENTATION;
                return ans;
            }
            else {
                timer.start();
                auto ans = dispatch_compile<traits>(ir);
                timer.pause();
                return ans;
            }
        }
        else {
            return dispatch_compile<traits>(ir);
        }
    }

    template <kinet::Traits traits>
    Binary
    dispatch_compile(kinet::vm::compiler::basic_blocks::BasicBlocksIR const &ir)
    {
        std::shared_ptr<kinet::vm::compiler::native::Nativecode> nc =
            kinet::vm::compiler::native::compile_basic_blocks<traits>(
                rt_, ir, config_);
        if (!nc->entrypoint()) {
            LOG_ERROR("Compilation failed.");
            kinet::flush_logger();
            abort();
        }

        return CompilerBinary{nc};
    }

private:
    asmjit::JitRuntime &rt_;
    kinet::vm::compiler::native::CompilerConfig const &config_;
};
