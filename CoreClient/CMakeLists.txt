if (TARGET core_client)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(core_client)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(CORE_CLIENT_IS_ROOT)

add_subdirectory("../CoreCommon" "${CMAKE_CURRENT_BINARY_DIR}/CoreCommon")

option(CORE_CLIENT_CI "We are running on CI. May change certain defaults." OFF)
if (CORE_CLIENT_CI)
    message(STATUS "CoreClient running on CI")
endif()

if (CORE_CLIENT_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(CORE_CLIENT_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(CORE_CLIENT_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(CORE_CLIENT_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CORE_CLIENT_TESTS "Build the core_client tests" ${CORE_CLIENT_IS_ROOT_AND_NOT_EMS})
option(CORE_CLIENT_BENCHMARKS "Build the core_client benchmarks" ${CORE_CLIENT_IS_ROOT_AND_NOT_EMS})
option(CORE_CLIENT_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(CORE_CLIENT_CLANG_FORMAT_CHECK "Adds the core_client_clang_format_check target" OFF)
option(CORE_CLIENT_CLANG_FORMAT_FIX "Adds the core_client_clang_format_fix target" OFF)
option(CORE_CLIENT_CPPCHECK "Adds the core_client_cppcheck target" OFF)
option(CORE_CLIENT_CLANG_TIDY_CHECK "Adds the core_client_clang_tidy_check target" OFF)
option(CORE_CLIENT_ASAN "Build with ASAN" OFF)
option(CORE_CLIENT_LSAN "Build with LSAN" OFF)
option(CORE_CLIENT_TSAN "Build with TSAN" OFF)
option(CORE_CLIENT_UBSAN "Build with UBSAN" OFF)
option(CORE_CLIENT_CODE_COVERAGE "Enable code coverage" OFF)
option(CORE_CLIENT_WARNINGS_AS_ERRORS "Treat warnings as errors" ${CORE_CLIENT_CI})
option(CORE_CLIENT_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (CORE_CLIENT_IS_ROOT)
    message(STATUS "CoreClient is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (CORE_CLIENT_DOWNLOAD_CPM)
    message(STATUS "CoreClient CPM Download Enabled")
    include(DownloadCPM)
endif()

if (CORE_CLIENT_ASAN)
    message(STATUS "CoreClient ASAN Enabled")
    include(SanitizeAddress)
endif()

if (CORE_CLIENT_LSAN)
    message(STATUS "CoreClient LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (CORE_CLIENT_TSAN)
    message(STATUS "CoreClient TSAN Enabled")
    include(SanitizeThreads)
endif()

if (CORE_CLIENT_UBSAN)
    message(STATUS "CoreClient UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (CORE_CLIENT_VALGRND)
    message(STATUS "CoreClient Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (CORE_CLIENT_TESTS)
    message(STATUS "CoreClient Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (CORE_CLIENT_BENCHMARKS)
    message(STATUS "CoreClient Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(CORE_CLIENT_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (CORE_CLIENT_CLANG_FORMAT_CHECK)
    message(STATUS "CoreClient clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "core_client_clang_format_check"
        "${CORE_CLIENT_LINT_PATHS}"
    )
endif()

if (CORE_CLIENT_CLANG_FORMAT_FIX)
    message(STATUS "CoreClient clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "core_client_clang_format_fix"
        "${CORE_CLIENT_LINT_PATHS}"
    )
endif()

if (CORE_CLIENT_CPPCHECK)
    message(STATUS "CoreClient cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(core_client_cppcheck
        "CoreClient/"
        "${CORE_CLIENT_LINT_PATHS}"
    )
endif()

if (CORE_CLIENT_CLANG_TIDY_CHECK)
    message(STATUS "CoreClient clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(core_client_clang_tidy_check "CoreClient/")
endif()