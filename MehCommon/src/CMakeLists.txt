include(ConfigureTarget)
include(CompilerWarnings)

add_library(meh_common
    "MehCommon/Library.hpp"
    "MehCommon/Library.cpp"
)
add_library(meh::common ALIAS meh_common)

target_link_libraries(meh_common PUBLIC core::common)
target_include_directories(meh_common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(meh_common PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    include(FetchSDL2)
    find_package(OpenGL)

    # glad is available from a previous call to add_subdirectory("dependencies")
    target_link_libraries(meh_common PUBLIC SDL2-static OpenGL::GL glad)

    if (UNIX AND NOT APPLE)
        target_link_libraries(meh_common PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

configure_target(meh_common "${MEH_COMMON_CODE_COVERAGE}")
set_target_warnings(meh_common "${MEH_COMMON_WARNINGS_AS_ERRORS}")