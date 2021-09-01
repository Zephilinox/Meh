include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(core_client_tests
    "main.cpp"
    "core_client.hpp"
)

configure_target(core_client_tests ${CORE_CLIENT_CODE_COVERAGE})
set_target_warnings(core_client_tests ${CORE_CLIENT_WARNINGS_AS_ERRORS})

target_link_libraries(core_client_tests
    PRIVATE
        core::client
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(core_client_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(core_client_tests)