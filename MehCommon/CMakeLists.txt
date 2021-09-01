if (TARGET meh_common)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(meh_common)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(MEH_COMMON_IS_ROOT)

add_subdirectory("../CoreCommon" "${CMAKE_CURRENT_BINARY_DIR}/CoreCommon")

option(MEH_COMMON_CI "We are running on CI. May change certain defaults." OFF)
if (MEH_COMMON_CI)
    message(STATUS "MehCommon running on CI")
endif()

if (MEH_COMMON_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(MEH_COMMON_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(MEH_COMMON_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(MEH_COMMON_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MEH_COMMON_TESTS "Build the meh_common tests" ${MEH_COMMON_IS_ROOT_AND_NOT_EMS})
option(MEH_COMMON_BENCHMARKS "Build the meh_common benchmarks" ${MEH_COMMON_IS_ROOT_AND_NOT_EMS})
option(MEH_COMMON_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(MEH_COMMON_CLANG_FORMAT_CHECK "Adds the meh_common_clang_format_check target" OFF)
option(MEH_COMMON_CLANG_FORMAT_FIX "Adds the meh_common_clang_format_fix target" OFF)
option(MEH_COMMON_CPPCHECK "Adds the meh_common_cppcheck target" OFF)
option(MEH_COMMON_CLANG_TIDY_CHECK "Adds the meh_common_clang_tidy_check target" OFF)
option(MEH_COMMON_ASAN "Build with ASAN" OFF)
option(MEH_COMMON_LSAN "Build with LSAN" OFF)
option(MEH_COMMON_TSAN "Build with TSAN" OFF)
option(MEH_COMMON_UBSAN "Build with UBSAN" OFF)
option(MEH_COMMON_CODE_COVERAGE "Enable code coverage" OFF)
option(MEH_COMMON_WARNINGS_AS_ERRORS "Treat warnings as errors" ${MEH_COMMON_CI})
option(MEH_COMMON_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (MEH_COMMON_IS_ROOT)
    message(STATUS "MehCommon is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (MEH_COMMON_DOWNLOAD_CPM)
    message(STATUS "MehCommon CPM Download Enabled")
    include(DownloadCPM)
endif()

if (MEH_COMMON_ASAN)
    message(STATUS "MehCommon ASAN Enabled")
    include(SanitizeAddress)
endif()

if (MEH_COMMON_LSAN)
    message(STATUS "MehCommon LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (MEH_COMMON_TSAN)
    message(STATUS "MehCommon TSAN Enabled")
    include(SanitizeThreads)
endif()

if (MEH_COMMON_UBSAN)
    message(STATUS "MehCommon UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (MEH_COMMON_VALGRND)
    message(STATUS "MehCommon Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (MEH_COMMON_TESTS)
    message(STATUS "MehCommon Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (MEH_COMMON_BENCHMARKS)
    message(STATUS "MehCommon Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(MEH_COMMON_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (MEH_COMMON_CLANG_FORMAT_CHECK)
    message(STATUS "MehCommon clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "meh_common_clang_format_check"
        "${MEH_COMMON_LINT_PATHS}"
    )
endif()

if (MEH_COMMON_CLANG_FORMAT_FIX)
    message(STATUS "MehCommon clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "meh_common_clang_format_fix"
        "${MEH_COMMON_LINT_PATHS}"
    )
endif()

if (MEH_COMMON_CPPCHECK)
    message(STATUS "MehCommon cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(meh_common_cppcheck
        "MehCommon/"
        "${MEH_COMMON_LINT_PATHS}"
    )
endif()

if (MEH_COMMON_CLANG_TIDY_CHECK)
    message(STATUS "MehCommon clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(meh_common_clang_tidy_check "MehCommon/")
endif()