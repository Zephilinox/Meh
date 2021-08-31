if (TARGET magic_enum)
    return()
endif()

include(SetSystemIncludes)

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${PROJECT_SOURCE_DIR}/../.cpmcache/")
endif()

CPMAddPackage(
    NAME magic_enum
    GITHUB_REPOSITORY Neargye/magic_enum
    GIT_TAG v0.7.3
    EXCLUDE_FROM_ALL "YES"
)

set_target_properties(magic_enum PROPERTIES FOLDER dependencies)
set_target_includes_as_system(magic_enum)