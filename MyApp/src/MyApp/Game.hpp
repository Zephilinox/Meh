#pragma once

//SELF

//LIBS
#include <CommonLib/Window/Window.hpp>
#include <CommonLib/Input/Input.hpp>

//STD
#include <array>

namespace meh::common
{
class WindowSDL;
}

//todo: won't need this when we have abstractions
struct ImGuiIO;

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
    std::unique_ptr<meh::common::Window> window;
    meh::common::WindowSDL* window_sdl = nullptr; //todo: not needed when we have proper abstractions everywhere
    void* glc;                                    //todo: hide in renderer?
    meh::common::Input input;

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