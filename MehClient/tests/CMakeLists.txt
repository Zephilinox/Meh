include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(meh_client_tests
    "main.cpp"
    "meh_client.hpp"
)

configure_target(meh_client_tests "${MEH_CLIENT_CODE_COVERAGE}")
set_target_warnings(meh_client_tests "${MEH_CLIENT_WARNINGS_AS_ERRORS}")

target_link_libraries(meh_client_tests
    PRIVATE
        meh_client
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(meh_client_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(meh_client_tests)