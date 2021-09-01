include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(core_common_tests
    "main.cpp"
    "core_common.hpp"
    "Signal.test.hpp"
)

configure_target(core_common_tests ${CORE_COMMON_CODE_COVERAGE})
set_target_warnings(core_common_tests ${CORE_COMMON_WARNINGS_AS_ERRORS})

target_link_libraries(core_common_tests
    PRIVATE
        core::common
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(core_common_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(core_common_tests)