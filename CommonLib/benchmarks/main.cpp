//SELF
#include "Signal.bench.hpp"

//LIBS
#include <benchmark/benchmark.h>

//STD

auto main(int argc, char** argv) -> int
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}