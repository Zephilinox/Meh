include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(core_server_tests
    "main.cpp"
    "core_server.hpp"
)

configure_target(core_server_tests ${CORE_SERVER_CODE_COVERAGE})
set_target_warnings(core_server_tests ${CORE_SERVER_WARNINGS_AS_ERRORS})

target_link_libraries(core_server_tests
    PRIVATE
        core::server
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(core_server_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(core_server_tests)