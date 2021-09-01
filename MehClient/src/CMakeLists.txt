include(ConfigureTarget)
include(CompilerWarnings)
include(FetchIMGUI)

add_library(meh_client OBJECT
    "MehClient/Game.hpp"
    "MehClient/Game.cpp"
)
add_library(meh::client ALIAS meh_client)

target_link_libraries(meh_client PUBLIC meh::common core::client imgui)
target_include_directories(meh_client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(meh_client PUBLIC "-sUSE_SDL=2" "-sUSE_FREETYPE=1")
else()
    if (UNIX AND NOT APPLE)
        target_link_libraries(meh_client PUBLIC "m" "atomic" "pthread")
    endif ()
endif()

configure_target(meh_client "${MEH_CLIENT_CODE_COVERAGE}")
set_target_warnings(meh_client "${MEH_CLIENT_WARNINGS_AS_ERRORS}")

add_executable(meh_client_executable "main.cpp")
target_link_libraries(meh_client_executable PUBLIC meh_client)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(
        meh_client_executable
        PROPERTIES 
            SUFFIX ".html" #change to ".wasm" if you only want the wasm output
    )
endif()

configure_target(meh_client_executable "${MEH_CLIENT_CODE_COVERAGE}")
set_target_warnings(meh_client_executable "${MEH_CLIENT_WARNINGS_AS_ERRORS}")