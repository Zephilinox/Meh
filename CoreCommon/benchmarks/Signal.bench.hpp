#pragma once

//SELF
#include "CoreCommon/Signal/Signal.hpp"

//LIBS
#include <benchmark/benchmark.h>

//STD
#include <memory>

struct Base
{
    virtual void do_thing(int) = 0;
    virtual ~Base() = default;
};

struct Derived : public Base
{
    void do_thing(int a) override
    {
        if (a != 5)
            throw;
    }
};

static void bench_virtual_int(benchmark::State& state)
{
    std::unique_ptr<Base> thing;
    thing = std::make_unique<Derived>();

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        thing->do_thing(5);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations()));
}
BENCHMARK(bench_virtual_int);

static void bench_signal_emit_int_1_slot(benchmark::State& state)
{
    core::common::Signal<int> signal;
    signal.connect([](int a) {
        if (a != 5)
            throw;
    });

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        signal.emit(5);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations()));
}
BENCHMARK(bench_signal_emit_int_1_slot);

static void bench_signal_emit_int_100_slots(benchmark::State& state)
{
    core::common::Signal<int> signal;
    for (int i = 0; i < 100; ++i)
    {
        signal.connect([](int a) {
            if (a != 5)
                throw;
        });
    }

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        signal.emit(5);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations() * 100));
}
BENCHMARK(bench_signal_emit_int_100_slots);

static void bench_signal_emit_int_10000_slots(benchmark::State& state)
{
    core::common::Signal<int> signal;
    for (int i = 0; i < 10000; ++i)
    {
        signal.connect([](int a) {
            if (a != 5)
                throw;
        });
    }

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        signal.emit(5);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations() * 10000));
}
BENCHMARK(bench_signal_emit_int_10000_slots);

static void bench_signal_connect(benchmark::State& state)
{
    core::common::Signal<int> signal;
    auto lambda = [](int a) {
        if (a != 5)
            throw;
    };

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        signal.connect(lambda);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations()));
}
BENCHMARK(bench_signal_connect);

static void bench_signal_disconnect(benchmark::State& state)
{
    core::common::Signal<int> signal;
    auto lambda = [](int a) {
        if (a != 5)
            throw;
    };

    for ([[maybe_unused]] auto _ : state) // NOLINT(clang-analyzer-deadcode.DeadStores)
    {
        core::common::ManagedConnection mc = signal.connect(lambda);
    }

    state.SetItemsProcessed(static_cast<std::int64_t>(state.iterations()));
}
BENCHMARK(bench_signal_disconnect);
