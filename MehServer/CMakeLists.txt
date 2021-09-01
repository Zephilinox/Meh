if (TARGET meh_server)
    return()
endif()

cmake_minimum_required(VERSION 3.21)

project(meh_server)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

include(CheckIsRoot)
check_project_is_root(MEH_SERVER_IS_ROOT)

add_subdirectory("../MehCommon" "${CMAKE_CURRENT_BINARY_DIR}/MehCommon")
add_subdirectory("../CoreServer" "${CMAKE_CURRENT_BINARY_DIR}/CoreServer")

option(MEH_SERVER_CI "We are running on CI. May change certain defaults." OFF)
if (MEH_SERVER_CI)
    message(STATUS "MehServer running on CI")
endif()

if (MEH_SERVER_IS_ROOT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(MEH_SERVER_IS_ROOT_AND_NOT_EMS OFF)
    else()
        set(MEH_SERVER_IS_ROOT_AND_NOT_EMS ON)
    endif()
else()
    set(MEH_SERVER_IS_ROOT_AND_NOT_EMS OFF)
endif()

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/../.cpmcache")
endif()

# todo: don't override the users choice
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MEH_SERVER_TESTS "Build the meh_server tests" ${MEH_SERVER_IS_ROOT_AND_NOT_EMS})
option(MEH_SERVER_BENCHMARKS "Build the meh_server benchmarks" ${MEH_SERVER_IS_ROOT_AND_NOT_EMS})
option(MEH_SERVER_INSTALL "Enable cmake install for the meh_server" ${MEH_SERVER_IS_ROOT})
option(MEH_SERVER_DOWNLOAD_CPM "Download CPM. Disable if you're providing your own version of CPM" ON)
option(MEH_SERVER_CLANG_FORMAT_CHECK "Adds the meh_server_clang_format_check target" OFF)
option(MEH_SERVER_CLANG_FORMAT_FIX "Adds the meh_server_clang_format_fix target" OFF)
option(MEH_SERVER_CPPCHECK "Adds the meh_server_cppcheck target" OFF)
option(MEH_SERVER_CLANG_TIDY_CHECK "Adds the meh_server_clang_tidy_check target" OFF)
option(MEH_SERVER_ASAN "Build with ASAN" OFF)
option(MEH_SERVER_LSAN "Build with LSAN" OFF)
option(MEH_SERVER_TSAN "Build with TSAN" OFF)
option(MEH_SERVER_UBSAN "Build with UBSAN" OFF)
option(MEH_SERVER_CODE_COVERAGE "Enable code coverage" OFF)
option(MEH_SERVER_WARNINGS_AS_ERRORS "Treat warnings as errors" ${MEH_SERVER_CI})
option(MEH_SERVER_VALGRIND "Use valgrind to run all executables" OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../dependencies" "${CMAKE_CURRENT_BINARY_DIR}/dependencies")

if (MEH_SERVER_IS_ROOT)
    message(STATUS "MehServer is root")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if (MEH_SERVER_DOWNLOAD_CPM)
    message(STATUS "MehServer CPM Download Enabled")
    include(DownloadCPM)
endif()

if (MEH_SERVER_ASAN)
    message(STATUS "MehServer ASAN Enabled")
    include(SanitizeAddress)
endif()

if (MEH_SERVER_LSAN)
    message(STATUS "MehServer LSAN Enabled")
    include(SanitizeLeaks)
endif()

if (MEH_SERVER_TSAN)
    message(STATUS "MehServer TSAN Enabled")
    include(SanitizeThreads)
endif()

if (MEH_SERVER_UBSAN)
    message(STATUS "MehServer UBSAN Enabled")
    include(SanitizeUndefinedBehaviour)
endif()

if (MEH_SERVER_VALGRND)
    message(STATUS "MehServer Valgrind Enabled")
    include(Valgrind)
endif()

add_subdirectory("src")

if (MEH_SERVER_INSTALL)
    message(STATUS "MehServer Install Enabled")
    install(
        DIRECTORY "$<TARGET_FILE_DIR:meh_server_executable>"
        DESTINATION "."
    )
endif()

if (MEH_SERVER_TESTS)
    message(STATUS "MehServer Tests Enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

if (MEH_SERVER_BENCHMARKS)
    message(STATUS "MehServer Benchmarks Enabled")
    add_subdirectory(benchmarks)
endif()

set(MEH_SERVER_LINT_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks"
)

if (MEH_SERVER_CLANG_FORMAT_CHECK)
    message(STATUS "MehServer clang-format check Enabled")
    include(ClangFormat)
    create_clang_format_check(
        "meh_server_clang_format_check"
        "${MEH_SERVER_LINT_PATHS}"
    )
endif()

if (MEH_SERVER_CLANG_FORMAT_FIX)
    message(STATUS "MehServer clang-format fix Enabled")
    include(ClangFormat)
    create_clang_format_fix(
        "meh_server_clang_format_fix"
        "${MEH_SERVER_LINT_PATHS}"
    )
endif()

if (MEH_SERVER_CPPCHECK)
    message(STATUS "MehServer cppcheck Enabled")
    include(CPPCheck)
    cppcheck_sources(meh_server_cppcheck
        "MehServer/"
        "${MEH_SERVER_LINT_PATHS}"
    )
endif()

if (MEH_SERVER_CLANG_TIDY_CHECK)
    message(STATUS "MehServer clang-tidy check Enabled")
    include(ClangTidy)
    create_clang_tidy_check(meh_server_clang_tidy_check "MehServer/")
endif()