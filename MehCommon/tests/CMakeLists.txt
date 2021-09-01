include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(meh_common_tests
    "main.cpp"
    "meh_common.hpp"
)

configure_target(meh_common_tests ${MEH_COMMON_CODE_COVERAGE})
set_target_warnings(meh_common_tests ${MEH_COMMON_WARNINGS_AS_ERRORS})

target_link_libraries(meh_common_tests
    PRIVATE
        meh::common
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(meh_common_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(meh_common_tests)