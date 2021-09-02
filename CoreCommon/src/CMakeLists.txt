include(ConfigureTarget)
include(CompilerWarnings)
include(FetchASIO)
include(FetchGLM)
include(FetchFMT)
include(FetchSPDLOG)
include(FetchMagicEnum)

add_library(core_common
    "CoreCommon/Window/Window.hpp"
    "CoreCommon/Window/WindowSDL.hpp"
    "CoreCommon/Window/WindowSDL.cpp"
    "CoreCommon/Window/WindowNone.hpp"
    "CoreCommon/Window/WindowNone.cpp"

    "CoreCommon/Input/Input.hpp"
    "CoreCommon/Input/Input.cpp"
    "CoreCommon/Input/Events.hpp"
    "CoreCommon/Input/Keys.hpp"
    "CoreCommon/Input/Keys.cpp"
    "CoreCommon/Input/KeysSDL.hpp"

    "CoreCommon/Signal/Connection.hpp"
    "CoreCommon/Signal/Connection.cpp"
    "CoreCommon/Signal/Disconnector.hpp"
    "CoreCommon/Signal/Signal.hpp"
    "CoreCommon/Signal/Slot.hpp"

    "CoreCommon/IMGUI/IMGUI.hpp"
    "CoreCommon/IMGUI/IMGUI_SDL_GL.hpp"
    "CoreCommon/IMGUI/IMGUI_SDL_GL.cpp"
)
add_library(core::common ALIAS core_common)

target_include_directories(core_common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(core_common PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    include(FetchSDL2)
    find_package(OpenGL)

    # glad is available from a previous call to add_subdirectory("dependencies")
    target_link_libraries(core_common PUBLIC SDL2-static OpenGL::GL glad)

    if (UNIX AND NOT APPLE)
        target_link_libraries(core_common PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

include(FetchIMGUI)
target_link_libraries(core_common
    PUBLIC
        fmt::fmt
        spdlog::spdlog
        magic_enum::magic_enum
        glm
        asio
        imgui
)
configure_target(core_common "${CORE_COMMON_CODE_COVERAGE}")
set_target_warnings(core_common "${CORE_COMMON_WARNINGS_AS_ERRORS}")