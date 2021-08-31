if (TARGET commonlib)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(commonlib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(COMMONLIB_IS_ROOT)

option(COMMONLIB_CI "We are running on CI. May change certain defaults." OFF)
if (COMMONLIB_CI)
    message(STATUS "CommonLib running on CI")
endif()

if (COMMONLIB_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(COMMONLIB_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(COMMONLIB_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(COMMONLIB_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

option(COMMONLIB_TESTS "Build the commonlib tests" ${COMMONLIB_IS_ROOT_AND_NOT_EMS})
option(COMMONLIB_BENCHMARKS "Build the commonlib benchmarks" ${COMMONLIB_IS_ROOT_AND_NOT_EMS})
option(COMMONLIB_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(COMMONLIB_CLANG_FORMAT_CHECK "Adds the commonlib_clang_format_check target" OFF)
option(COMMONLIB_CLANG_FORMAT_FIX "Adds the commonlib_clang_format_fix target" OFF)
option(COMMONLIB_CPPCHECK "Adds the commonlib_cppcheck target" OFF)
option(COMMONLIB_CLANG_TIDY_CHECK "Adds the commonlib_clang_tidy_check target" OFF)
option(COMMONLIB_ASAN "Build with ASAN" OFF)
option(COMMONLIB_LSAN "Build with LSAN" OFF)
option(COMMONLIB_TSAN "Build with TSAN" OFF)
option(COMMONLIB_UBSAN "Build with UBSAN" OFF)
option(COMMONLIB_CODE_COVERAGE "Enable code coverage" OFF)
option(COMMONLIB_WARNINGS_AS_ERRORS "Treat warnings as errors" ${COMMONLIB_CI})
option(COMMONLIB_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (COMMONLIB_IS_ROOT)
    message(STATUS "CommonLib is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (COMMONLIB_DOWNLOAD_CPM)
    message(STATUS "CommonLib CPM Download Enabled")
    include(DownloadCPM)
endif()

if (COMMONLIB_ASAN)
    message(STATUS "CommonLib ASAN Enabled")
    include(SanitizeAddress)
endif()

if (COMMONLIB_LSAN)
    message(STATUS "CommonLib LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (COMMONLIB_TSAN)
    message(STATUS "CommonLib TSAN Enabled")
    include(SanitizeThreads)
endif()

if (COMMONLIB_UBSAN)
    message(STATUS "CommonLib UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (COMMONLIB_VALGRND)
    message(STATUS "CommonLib Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (COMMONLIB_TESTS)
    message(STATUS "CommonLib Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (COMMONLIB_BENCHMARKS)
    message(STATUS "CommonLib Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(COMMONLIB_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (COMMONLIB_CLANG_FORMAT_CHECK)
    message(STATUS "CommonLib clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "commonlib_clang_format_check"
        "${COMMONLIB_LINT_PATHS}"
    )
endif()

if (COMMONLIB_CLANG_FORMAT_FIX)
    message(STATUS "CommonLib clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "commonlib_clang_format_fix"
        "${COMMONLIB_LINT_PATHS}"
    )
endif()

if (COMMONLIB_CPPCHECK)
    message(STATUS "CommonLib cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(commonlib_cppcheck
        "CommonLib/"
        "${COMMONLIB_LINT_PATHS}"
    )
endif()

if (COMMONLIB_CLANG_TIDY_CHECK)
    message(STATUS "CommonLib clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(commonlib_clang_tidy_check "CommonLib/")
endif()