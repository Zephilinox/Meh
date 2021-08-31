include(FetchGoogleBenchmark)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(commonlib_benchmarks "main.cpp"
    "Signal.bench.hpp"
)

configure_target(commonlib_benchmarks "${COMMONLIB_CODE_COVERAGE}")
set_target_warnings(commonlib_benchmarks "${COMMONLIB_WARNINGS_AS_ERRORS}")

target_link_libraries(commonlib_benchmarks
    PRIVATE
        commonlib::commonlib
        benchmark::benchmark
)

# Don't use the crosscompiling executor, if it's valgrind they will be very slow.
# We'll rely on static analysis for benchmark leaks. in theory, tests should cover it.
# Also, googlebenchmark has an intentional memory leak, so we'd need to supress it.
add_custom_target(commonlib_benchmarks_execute
    COMMAND "$<TARGET_FILE:commonlib_benchmarks>"
)