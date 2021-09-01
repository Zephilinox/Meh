include(ConfigureTarget)
include(CompilerWarnings)
include(FetchIMGUI)

add_library(meh_server OBJECT
    "MehServer/Game.hpp"
    "MehServer/Game.cpp"
)
add_library(meh::server ALIAS meh_server)

target_link_libraries(meh_server PUBLIC meh::common core::server imgui)
target_include_directories(meh_server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(meh_server PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    if (UNIX AND NOT APPLE)
        target_link_libraries(meh_server PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

configure_target(meh_server "${MEH_SERVER_CODE_COVERAGE}")
set_target_warnings(meh_server "${MEH_SERVER_WARNINGS_AS_ERRORS}")

add_executable(meh_server_executable "main.cpp")
target_link_libraries(meh_server_executable PUBLIC meh_server)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(
        meh_server_executable
        PROPERTIES 
            SUFFIX ".html" #change to ".wasm" if you only want the wasm output
    )
endif()

configure_target(meh_server_executable "${MEH_SERVER_CODE_COVERAGE}")
set_target_warnings(meh_server_executable "${MEH_SERVER_WARNINGS_AS_ERRORS}")