include(SetSystemIncludes)

CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm
    GIT_TAG 0.9.9.8
)

set_target_includes_as_system(glm)
set_target_warnings_disabled(glm)