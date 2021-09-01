include(FetchGoogleBenchmark)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(meh_client_benchmarks
    "main.cpp"
)

configure_target(meh_client_benchmarks ${MEH_CLIENT_CODE_COVERAGE})
set_target_warnings(meh_client_benchmarks ${MEH_CLIENT_WARNINGS_AS_ERRORS})

target_link_libraries(meh_client_benchmarks
    PRIVATE
        meh_client
        benchmark::benchmark
)

# Don't use the crosscompiling executor, if it's valgrind they will be very slow.
# We'll rely on static analysis for benchmark leaks. in theory, tests should cover it.
# Also, googlebenchmark has an intentional memory leak, so we'd need to supress it.
add_custom_target(meh_client_benchmarks_execute
    COMMAND "$<TARGET_FILE:meh_client_benchmarks>"
)