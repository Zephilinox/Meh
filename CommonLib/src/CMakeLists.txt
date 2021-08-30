include(ConfigureTarget)
include(CompilerWarnings)
include(FetchAsio)
include(FetchGLM)
include(FetchFMT)
include(FetchSPDLOG)

add_library(commonlib
    "CommonLib/Window/Window.hpp"
    "CommonLib/Window/WindowSDL.hpp"
    "CommonLib/Window/WindowSDL.cpp"
    "CommonLib/Window/WindowNone.hpp"
    "CommonLib/Window/WindowNone.cpp"
)
add_library(commonlib::commonlib ALIAS commonlib)

target_include_directories(commonlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(commonlib PUBLIC fmt::fmt spdlog::spdlog)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(commonlib PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    include(FetchSDL2)
    find_package(OpenGL)

    # glad is available from a previous call to add_subdirectory("dependencies")
    target_link_libraries(commonlib PUBLIC SDL2-static OpenGL::GL glad)

    if (UNIX AND NOT APPLE)
        target_link_libraries(commonlib PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

target_link_libraries(commonlib PUBLIC glm asio)

configure_target(commonlib "${COMMONLIB_CODE_COVERAGE}")
set_target_warnings(commonlib "${COMMONLIB_WARNINGS_AS_ERRORS}")