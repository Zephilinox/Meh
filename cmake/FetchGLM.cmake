if (TARGET glm)
    return()
endif()

include(SetSystemIncludes)

if (NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${PROJECT_SOURCE_DIR}/../.cpmcache/")
endif()

CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm
    GIT_TAG 0.9.9.8
)