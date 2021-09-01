include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(meh_server_tests
    "main.cpp"
    "meh_server.hpp"
)

configure_target(meh_server_tests ${MEH_SERVER_CODE_COVERAGE})
set_target_warnings(meh_server_tests ${MEH_SERVER_WARNINGS_AS_ERRORS})

target_link_libraries(meh_server_tests
    PRIVATE
        meh::server
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(meh_server_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(meh_server_tests)