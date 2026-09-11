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

#include <category/execution/kinet/staking/fuzzer/staking_contract_machine.hpp>
#include <category/execution/kinet/staking/test/input_generation.hpp>
#include <category/vm/evm/kinet/revision.h>
#include <category/vm/evm/switch_traits.hpp>
#include <category/vm/evm/traits.hpp>

#include <CLI/CLI.hpp>

#include <evmc/evmc.hpp>

using namespace kinet;
using namespace kinet::staking;
using namespace kinet::staking::test;
using namespace kinet::staking::test::fuzzing;
using namespace kinet::literals;

template <Traits traits>
using Transition = StakingContractMachine<traits>::Transition;

template <Traits traits>
static Transition<traits>
gen_transition(StakingContractMachine<traits> &machine)
{
    auto const p = machine.gen() % 100;
    if (p < 30) {
        if (p < 20) {
            return Transition<traits>::syscall_reward;
        }
        return Transition<traits>::precompile_external_reward;
    }
    return machine.gen_transition();
}

template <Traits traits>
static seed_t run_simulation(seed_t seed, uint64_t depth)
{
    KINET_ASSERT(depth > 0);

    std::cout << "Simulation with seed " << seed << std::endl;

    auto const start_time = std::chrono::steady_clock::now();

    StakingContractMachine<traits> machine{seed};
    double success_count = 0;
    for (size_t i = 0; i < depth; ++i) {
        if (machine.transition(gen_transition(machine))) {
            ++success_count;
        }
    }

    auto const end_time = std::chrono::steady_clock::now();

    auto const success_ratio = success_count / static_cast<double>(depth);
    auto const time =
        static_cast<double>((end_time - start_time).count()) / 1'000'000;

    std::cout << "    success ratio: " << success_ratio << '\n'
              << "  simulation time: " << time << " ms" << std::endl;

    return machine.gen();
}

namespace
{
    struct CommandArgs
    {
        seed_t seed = 0;
        uint64_t depth = 100;
        uint64_t runs = std::numeric_limits<uint64_t>::max();
        kinet_revision kinet_rev = KINET_NEXT;
    };

    CommandArgs parse_args(int const argc, char **const argv)
    {
        auto app = CLI::App("Staking Contract Fuzzer");
        auto args = CommandArgs{};

        app.add_option(
            "--seed",
            args.seed,
            "Seed for reproducible fuzzing (0 by default)");

        app.add_option(
            "--depth",
            args.depth,
            "Staking contract transitions per simulation (default 100)");

        app.add_option(
            "--runs",
            args.runs,
            "Number of simulations to execute (default max uint64)");

        std::map<std::string, kinet_revision> rev_map;
        for (int i = static_cast<int>(KINET_ZERO);
             i <= static_cast<int>(KINET_NEXT);
             ++i) {
            rev_map.emplace(
                kinet_revision_to_string(static_cast<kinet_revision>(i)),
                static_cast<kinet_revision>(i));
        }

        app.add_option(
               "--kinet-rev",
               args.kinet_rev,
               "Kinet revision (default KINET_NEXT)")
            ->transform(CLI::CheckedTransformer(rev_map, CLI::ignore_case));

        try {
            app.parse(argc, argv);
        }
        catch (CLI::ParseError const &e) {
            std::exit(app.exit(e));
        }

        return args;
    }
}

int main(int const argc, char **const argv)
{
    auto const args = parse_args(argc, argv);

    std::cout << "Running " << args.runs << " simulations\n"
              << "  depth: " << args.depth << '\n'
              << "   seed: " << args.seed << '\n'
              << "    rev: " << kinet_revision_to_string(args.kinet_rev)
              << std::endl;

    auto const rev = args.kinet_rev;
    size_t seed = args.seed;
    for (size_t i = 0; i < args.runs; ++i) {
        seed = [rev, &seed, &args] -> seed_t {
            SWITCH_KINET_TRAITS(run_simulation, seed, args.depth);
            KINET_ABORT();
        }();
    }
}
