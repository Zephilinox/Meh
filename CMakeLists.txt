cmake_minimum_required(VERSION 3.21)

project(meh)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CheckIsRoot)
check_project_is_root(MEH_IS_ROOT)

if (NOT MEH_IS_ROOT)
    message(SEND_ERROR "Root CMakeLists.txt is for development only")
endif()

find_program(ClangTidy clang-tidy)
set(USE_CLANG_TIDY ON)
if (NOT ClangTidy)
    set(USE_CLANG_TIDY OFF)
endif()

find_program(ClangFormat clang-format)
set(USE_CLANG_FORMAT ON)
if (NOT ClangFormat)
    set(USE_CLANG_FORMAT OFF)
endif()

find_program(CPPCheck cppcheck)
set(USE_CPPCHECK ON)
if (NOT CPPCheck)
    set(USE_CPPCHECK OFF)
endif()

set(COMMONLIB_TESTS "${MEH_IS_ROOT}")
set(COMMONLIB_BENCHMARKS "${MEH_IS_ROOT}")
set(COMMONLIB_CLANG_TIDY_CHECK "${USE_CLANG_TIDY}")
set(COMMONLIB_CLANG_FORMAT_CHECK "${USE_CLANG_FORMAT}")
set(COMMONLIB_CLANG_FORMAT_FIX "${USE_CLANG_FORMAT}")
set(COMMONLIB_CPPCHECK "${USE_CPPCHECK}")
add_subdirectory("CommonLib")

set(MYLIB_TESTS "${MEH_IS_ROOT}")
set(MYLIB_BENCHMARKS "${MEH_IS_ROOT}")
set(MYLIB_CLANG_TIDY_CHECK "${USE_CLANG_TIDY}")
set(MYLIB_CLANG_FORMAT_CHECK "${USE_CLANG_FORMAT}")
set(MYLIB_CLANG_FORMAT_FIX "${USE_CLANG_FORMAT}")
set(MYLIB_CPPCHECK "${USE_CPPCHECK}")
add_subdirectory("MyLib")

set(MYAPP_TESTS "${MEH_IS_ROOT}")
set(MYAPP_BENCHMARKS "${MEH_IS_ROOT}")
set(MYAPP_CLANG_TIDY_CHECK "${USE_CLANG_TIDY}")
set(MYAPP_CLANG_FORMAT_CHECK "${USE_CLANG_FORMAT}")
set(MYAPP_CLANG_FORMAT_FIX "${USE_CLANG_FORMAT}")
set(MYAPP_CPPCHECK "${USE_CPPCHECK}")
add_subdirectory("MyApp")