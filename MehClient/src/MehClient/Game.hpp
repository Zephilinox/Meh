#pragma once

//SELF

//LIBS
#include <CoreCommon/Window/Window.hpp>
#include <CoreCommon/Input/Input.hpp>

//STD
#include <array>

namespace core::common
{

class WindowSDL;

}

//todo: won't need this when we have abstractions
struct ImGuiIO;

namespace meh::client
{

class Game
{
public:
    static int add(int, int);

    Game();
    ~Game();

    int run();

    void events();
    void update();
    void render();

private:
    std::unique_ptr<core::common::Window> window;
    core::common::WindowSDL* window_sdl = nullptr; //todo: not needed when we have proper abstractions everywhere
    void* glc;                                     //todo: hide in renderer?
    core::common::Input input;

    //todo: remove once we have some IMGUI windows we can use instead, or maybe hide behind a special key
    bool show_demo_window = true;

    //todo: lots of openGL specific stuff, that should live... somewhere else
    std::array<float, 6> vertices{ 0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f };
    const char* vertexSource = "attribute vec4 position;    \n"
                               "void main()                  \n"
                               "{                            \n"
                               "   gl_Position = vec4(position.xyz, 1.0);  \n"
                               "}                            \n";
    const char* fragmentSource = "precision mediump float;\n"
                                 "void main()                                  \n"
                                 "{                                            \n"
                                 "  gl_FragColor = vec4 (1.0, 1.0, 1.0, 1.0 );\n"
                                 "}                                            \n";

    //todo: remove once we have IMGUI abstraction
    ImGuiIO* io = nullptr;
};

} // namespace meh::client