if (TARGET core_server)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(core_server)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(CORE_SERVER_IS_ROOT)

add_subdirectory("../CoreCommon" "${CMAKE_CURRENT_BINARY_DIR}/CoreCommon")

option(CORE_SERVER_CI "We are running on CI. May change certain defaults." OFF)
if (CORE_SERVER_CI)
    message(STATUS "CoreServer running on CI")
endif()

if (CORE_SERVER_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(CORE_SERVER_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(CORE_SERVER_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(CORE_SERVER_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CORE_SERVER_TESTS "Build the core_server tests" ${CORE_SERVER_IS_ROOT_AND_NOT_EMS})
option(CORE_SERVER_BENCHMARKS "Build the core_server benchmarks" ${CORE_SERVER_IS_ROOT_AND_NOT_EMS})
option(CORE_SERVER_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(CORE_SERVER_CLANG_FORMAT_CHECK "Adds the core_server_clang_format_check target" OFF)
option(CORE_SERVER_CLANG_FORMAT_FIX "Adds the core_server_clang_format_fix target" OFF)
option(CORE_SERVER_CPPCHECK "Adds the core_server_cppcheck target" OFF)
option(CORE_SERVER_CLANG_TIDY_CHECK "Adds the core_server_clang_tidy_check target" OFF)
option(CORE_SERVER_ASAN "Build with ASAN" OFF)
option(CORE_SERVER_LSAN "Build with LSAN" OFF)
option(CORE_SERVER_TSAN "Build with TSAN" OFF)
option(CORE_SERVER_UBSAN "Build with UBSAN" OFF)
option(CORE_SERVER_CODE_COVERAGE "Enable code coverage" OFF)
option(CORE_SERVER_WARNINGS_AS_ERRORS "Treat warnings as errors" ${CORE_SERVER_CI})
option(CORE_SERVER_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (CORE_SERVER_IS_ROOT)
    message(STATUS "CoreServer is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (CORE_SERVER_DOWNLOAD_CPM)
    message(STATUS "CoreServer CPM Download Enabled")
    include(DownloadCPM)
endif()

if (CORE_SERVER_ASAN)
    message(STATUS "CoreServer ASAN Enabled")
    include(SanitizeAddress)
endif()

if (CORE_SERVER_LSAN)
    message(STATUS "CoreServer LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (CORE_SERVER_TSAN)
    message(STATUS "CoreServer TSAN Enabled")
    include(SanitizeThreads)
endif()

if (CORE_SERVER_UBSAN)
    message(STATUS "CoreServer UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (CORE_SERVER_VALGRND)
    message(STATUS "CoreServer Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (CORE_SERVER_TESTS)
    message(STATUS "CoreServer Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (CORE_SERVER_BENCHMARKS)
    message(STATUS "CoreServer Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(CORE_SERVER_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (CORE_SERVER_CLANG_FORMAT_CHECK)
    message(STATUS "CoreServer clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "core_server_clang_format_check"
        "${CORE_SERVER_LINT_PATHS}"
    )
endif()

if (CORE_SERVER_CLANG_FORMAT_FIX)
    message(STATUS "CoreServer clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "core_server_clang_format_fix"
        "${CORE_SERVER_LINT_PATHS}"
    )
endif()

if (CORE_SERVER_CPPCHECK)
    message(STATUS "CoreServer cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(core_server_cppcheck
        "CoreServer/"
        "${CORE_SERVER_LINT_PATHS}"
    )
endif()

if (CORE_SERVER_CLANG_TIDY_CHECK)
    message(STATUS "CoreServer clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(core_server_clang_tidy_check "CoreServer/")
endif()