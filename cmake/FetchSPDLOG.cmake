if (TARGET spdlog)
    return()
endif()

include(FetchFMT)
include(SetSystemIncludes)
include(CompilerWarnings)

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${PROJECT_SOURCE_DIR}/../.cpmcache/")
endif()

CPMAddPackage(
    NAME spdlog
    GITHUB_REPOSITORY gabime/spdlog
    GIT_TAG v1.9.2
    EXCLUDE_FROM_ALL "YES"
    OPTIONS
        "SPDLOG_FMT_EXTERNAL ON"
)

file(GLOB_RECURSE spdlog_SOURCES CONFIGURE_DEPENDS ${spdlog_SOURCE_DIR}/*.hpp ${spdlog_SOURCE_DIR}/*.h ${spdlog_SOURCE_DIR}/*.c ${spdlog_SOURCE_DIR}/*.cpp)

source_group(TREE ${spdlog_SOURCE_DIR} FILES ${spdlog_SOURCES})
set_target_properties(spdlog PROPERTIES FOLDER dependencies)
set_target_includes_as_system(spdlog)
set_target_warnings_disabled(spdlog)