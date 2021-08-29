if (TARGET fmt)
    return()
endif()

include(SetSystemIncludes)
include(CompilerWarnings)

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${PROJECT_SOURCE_DIR}/../.cpmcache/")
endif()

CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt
    GIT_TAG 8.0.1
    EXCLUDE_FROM_ALL "YES"
)

file(GLOB_RECURSE fmt_SOURCES CONFIGURE_DEPENDS ${fmt_SOURCE_DIR}/*.hpp ${fmt_SOURCE_DIR}/*.h ${fmt_SOURCE_DIR}/*.c ${fmt_SOURCE_DIR}/*.cpp)

source_group(TREE ${fmt_SOURCE_DIR} FILES ${fmt_SOURCES})
set_target_properties(fmt PROPERTIES FOLDER dependencies)
set_target_includes_as_system(fmt)
set_target_warnings_disabled(fmt)