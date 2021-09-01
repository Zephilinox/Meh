if (TARGET core_common)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(core_common)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(CORE_COMMON_IS_ROOT)

option(CORE_COMMON_CI "We are running on CI. May change certain defaults." OFF)
if (CORE_COMMON_CI)
    message(STATUS "CoreCommon running on CI")
endif()

if (CORE_COMMON_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(CORE_COMMON_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(CORE_COMMON_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(CORE_COMMON_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CORE_COMMON_TESTS "Build the core_common tests" ${CORE_COMMON_IS_ROOT_AND_NOT_EMS})
option(CORE_COMMON_BENCHMARKS "Build the core_common benchmarks" ${CORE_COMMON_IS_ROOT_AND_NOT_EMS})
option(CORE_COMMON_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(CORE_COMMON_CLANG_FORMAT_CHECK "Adds the core_common_clang_format_check target" OFF)
option(CORE_COMMON_CLANG_FORMAT_FIX "Adds the core_common_clang_format_fix target" OFF)
option(CORE_COMMON_CPPCHECK "Adds the core_common_cppcheck target" OFF)
option(CORE_COMMON_CLANG_TIDY_CHECK "Adds the core_common_clang_tidy_check target" OFF)
option(CORE_COMMON_ASAN "Build with ASAN" OFF)
option(CORE_COMMON_LSAN "Build with LSAN" OFF)
option(CORE_COMMON_TSAN "Build with TSAN" OFF)
option(CORE_COMMON_UBSAN "Build with UBSAN" OFF)
option(CORE_COMMON_CODE_COVERAGE "Enable code coverage" OFF)
option(CORE_COMMON_WARNINGS_AS_ERRORS "Treat warnings as errors" ${CORE_COMMON_CI})
option(CORE_COMMON_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (CORE_COMMON_IS_ROOT)
    message(STATUS "CoreCommon is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (CORE_COMMON_DOWNLOAD_CPM)
    message(STATUS "CoreCommon CPM Download Enabled")
    include(DownloadCPM)
endif()

if (CORE_COMMON_ASAN)
    message(STATUS "CoreCommon ASAN Enabled")
    include(SanitizeAddress)
endif()

if (CORE_COMMON_LSAN)
    message(STATUS "CoreCommon LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (CORE_COMMON_TSAN)
    message(STATUS "CoreCommon TSAN Enabled")
    include(SanitizeThreads)
endif()

if (CORE_COMMON_UBSAN)
    message(STATUS "CoreCommon UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (CORE_COMMON_VALGRND)
    message(STATUS "CoreCommon Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (CORE_COMMON_TESTS)
    message(STATUS "CoreCommon Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (CORE_COMMON_BENCHMARKS)
    message(STATUS "CoreCommon Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(CORE_COMMON_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (CORE_COMMON_CLANG_FORMAT_CHECK)
    message(STATUS "CoreCommon clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "core_common_clang_format_check"
        "${CORE_COMMON_LINT_PATHS}"
    )
endif()

if (CORE_COMMON_CLANG_FORMAT_FIX)
    message(STATUS "CoreCommon clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "core_common_clang_format_fix"
        "${CORE_COMMON_LINT_PATHS}"
    )
endif()

if (CORE_COMMON_CPPCHECK)
    message(STATUS "CoreCommon cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(core_common_cppcheck
        "CoreCommon/"
        "${CORE_COMMON_LINT_PATHS}"
    )
endif()

if (CORE_COMMON_CLANG_TIDY_CHECK)
    message(STATUS "CoreCommon clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(core_common_clang_tidy_check "CoreCommon/")
endif()