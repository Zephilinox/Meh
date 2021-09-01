cmake_minimum_required(VERSION 3.21)

project(meh_client)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(MEH_CLIENT_IS_ROOT)

add_subdirectory("../MehCommon" "${CMAKE_CURRENT_BINARY_DIR}/MehCommon")
add_subdirectory("../CoreClient" "${CMAKE_CURRENT_BINARY_DIR}/CoreClient")

option(MEH_CLIENT_CI "We are running on CI. May change certain defaults." OFF)
if (MEH_CLIENT_CI)
    message(STATUS "MehClient running on CI")
endif()

if (MEH_CLIENT_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(MEH_CLIENT_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(MEH_CLIENT_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(MEH_CLIENT_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MEH_CLIENT_TESTS "Build the meh_client tests" ${MEH_CLIENT_IS_ROOT_AND_NOT_EMS})
option(MEH_CLIENT_BENCHMARKS "Build the meh_client benchmarks" ${MEH_CLIENT_IS_ROOT_AND_NOT_EMS})
option(MEH_CLIENT_INSTALL "Enable cmake install for the meh_client" ${MEH_CLIENT_IS_ROOT})
option(MEH_CLIENT_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(MEH_CLIENT_CLANG_FORMAT_CHECK "Adds the meh_client_clang_format_check target" OFF)
option(MEH_CLIENT_CLANG_FORMAT_FIX "Adds the meh_client_clang_format_fix target" OFF)
option(MEH_CLIENT_CPPCHECK "Adds the meh_client_cppcheck target" OFF)
option(MEH_CLIENT_CLANG_TIDY_CHECK "Adds the meh_client_clang_tidy_check target" OFF)
option(MEH_CLIENT_ASAN "Build with ASAN" OFF)
option(MEH_CLIENT_LSAN "Build with LSAN" OFF)
option(MEH_CLIENT_TSAN "Build with TSAN" OFF)
option(MEH_CLIENT_UBSAN "Build with UBSAN" OFF)
option(MEH_CLIENT_CODE_COVERAGE "Enable code coverage" OFF)
option(MEH_CLIENT_WARNINGS_AS_ERRORS "Treat warnings as errors" ${MEH_CLIENT_CI})
option(MEH_CLIENT_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (MEH_CLIENT_IS_ROOT)
    message(STATUS "MehClient is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (MEH_CLIENT_DOWNLOAD_CPM)
    message(STATUS "MehClient CPM Download Enabled")
    include(DownloadCPM)
endif()

if (MEH_CLIENT_ASAN)
    message(STATUS "MehClient ASAN Enabled")
    include(SanitizeAddress)
endif()

if (MEH_CLIENT_LSAN)
    message(STATUS "MehClient LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (MEH_CLIENT_TSAN)
    message(STATUS "MehClient TSAN Enabled")
    include(SanitizeThreads)
endif()

if (MEH_CLIENT_UBSAN)
    message(STATUS "MehClient UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (MEH_CLIENT_VALGRND)
    message(STATUS "MehClient Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (MEH_CLIENT_INSTALL)
    message(STATUS "MehClient Install Enabled")
    install(
        DIRECTORY "$<TARGET_FILE_DIR:meh_client_executable>"
        DESTINATION "."
    )
endif()

if (MEH_CLIENT_TESTS)
    message(STATUS "MehClient Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (MEH_CLIENT_BENCHMARKS)
    message(STATUS "MehClient Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(MEH_CLIENT_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (MEH_CLIENT_CLANG_FORMAT_CHECK)
    message(STATUS "MehClient clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "meh_client_clang_format_check"
        "${MEH_CLIENT_LINT_PATHS}"
    )
endif()

if (MEH_CLIENT_CLANG_FORMAT_FIX)
    message(STATUS "MehClient clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "meh_client_clang_format_fix"
        "${MEH_CLIENT_LINT_PATHS}"
    )
endif()

if (MEH_CLIENT_CPPCHECK)
    message(STATUS "MehClient cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(meh_client_cppcheck
        "MehClient/"
        "${MEH_CLIENT_LINT_PATHS}"
    )
endif()

if (MEH_CLIENT_CLANG_TIDY_CHECK)
    message(STATUS "MehClient clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(meh_client_clang_tidy_check "MehClient/")
endif()