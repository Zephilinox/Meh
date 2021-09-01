include(ConfigureTarget)
include(CompilerWarnings)

add_library(core_server
    "CoreServer/Library.hpp"
    "CoreServer/Library.cpp"
)
add_library(core::server ALIAS core_server)

target_link_libraries(core_server PUBLIC core::common)
target_include_directories(core_server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(core_server PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    include(FetchSDL2)
    find_package(OpenGL)

    # glad is available from a previous call to add_subdirectory("dependencies")
    target_link_libraries(core_server PUBLIC SDL2-static OpenGL::GL glad)

    if (UNIX AND NOT APPLE)
        target_link_libraries(core_server PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

configure_target(core_server "${CORE_SERVER_CODE_COVERAGE}")
set_target_warnings(core_server "${CORE_SERVER_WARNINGS_AS_ERRORS}")