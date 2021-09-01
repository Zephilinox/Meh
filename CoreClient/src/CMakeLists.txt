include(ConfigureTarget)
include(CompilerWarnings)

add_library(core_client
    "CoreClient/Library.hpp"
    "CoreClient/Library.cpp"
)
add_library(core::client ALIAS core_client)

target_link_libraries(core_client PUBLIC core::common)
target_include_directories(core_client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(core_client PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    include(FetchSDL2)
    find_package(OpenGL)

    # glad is available from a previous call to add_subdirectory("dependencies")
    target_link_libraries(core_client PUBLIC SDL2-static OpenGL::GL glad)

    if (UNIX AND NOT APPLE)
        target_link_libraries(core_client PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

configure_target(core_client "${CORE_CLIENT_CODE_COVERAGE}")
set_target_warnings(core_client "${CORE_CLIENT_WARNINGS_AS_ERRORS}")