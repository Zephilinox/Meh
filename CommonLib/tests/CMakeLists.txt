include(FetchDoctest)
include(ConfigureTarget)
include(CompilerWarnings)

add_executable(commonlib_tests
    "main.cpp"
    "commonlib.hpp"
)

configure_target(commonlib_tests ${COMMONLIB_CODE_COVERAGE})
set_target_warnings(commonlib_tests ${COMMONLIB_WARNINGS_AS_ERRORS})

target_link_libraries(commonlib_tests
    PRIVATE
        commonlib::commonlib
        doctest::doctest
)

include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")
#doctest_discover_tests(commonlib_tests JUNIT_OUTPUT_DIR ".")
doctest_discover_tests(commonlib_tests)