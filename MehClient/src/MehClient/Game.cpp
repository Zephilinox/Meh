#include "Game.hpp"

//SELF

//LIBS
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>

    #define GL_GLEXT_PROTOTYPES 1
    #include <SDL_opengles2.h>
#else
    #undef main
    #include <glad/glad.h>
#endif

#include <MehCommon/Library.hpp>
#include <CoreCommon/Window/WindowSDL.hpp>
#include <CoreCommon/IMGUI/IMGUI_SDL_GL.hpp>

#include <cstring> //memcpy for SDL
#include <SDL.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

using namespace meh::client;

//STD

int Game::add(int a, int b)
{
    return a + b;
}

Game::Game()
{
    //todo: hide somewhere, must be done before anything SDL related
    SDL_Init(SDL_INIT_VIDEO);

    //todo: hide somewhere, must be done before making window, but after knowing what renderer we want
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    core::common::Window::Settings settings{ 1280, 720, "MehClient" };
    window = std::make_unique<core::common::WindowSDL>(settings);
    //todo: once we've abstracted everything, we shouldn't need to do this.
    window_sdl = window->as<core::common::WindowSDL>();

    //todo: hide in renderer
    glc = SDL_GL_CreateContext(window_sdl->getRawWindow());
    //todo: currently the window has settings for vsync, have the renderer use those to set vsync when it's created? or move vsync to the renderer?
    SDL_GL_SetSwapInterval(0); // VSync off, though when running in a browser it may get overriden

    //todo: hide in renderer
    if (!static_cast<bool>(gladLoadGLES2Loader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress))))
    {
        spdlog::error("Failed to initialize OpenGLES loader!\n");
        //todo: how to handle this failing (nicely?)
        throw;
    }

    spdlog::info("OpenGLES version loaded: {}.{}\n", GLVersion.major, GLVersion.minor);

    imgui = std::make_unique<core::common::IMGUI_SDL_GL>(*window, glc);

    //todo: this is nasty
    {
        // Create Vertex Array Object
        GLuint vao = 0;
        glGenVertexArraysOES(1, &vao);
        glBindVertexArrayOES(vao);

        // Create a Vertex Buffer Object and copy the vertex data to it
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(GLfloat)), vertices.data(), GL_STATIC_DRAW);

        // Create and compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);

        // Create and compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);

        // Link the vertex and fragment shader into a shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        // glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(static_cast<GLuint>(posAttrib));
        glVertexAttribPointer(static_cast<GLuint>(posAttrib), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
}

Game::~Game()
{
    imgui.reset();

    SDL_GL_DeleteContext(glc); //todo: let renderer do it
    window.reset();
    SDL_Quit(); //todo: let something else do it. not sure if window is correct, what if we end up wanting multiple windows?
}

int Game::run()
{
    while (window->isOpen())
    {
        events();
        update();
        render();
    }

    return 0;
}

void Game::events()
{
    input.prepare();

    core::common::Event event;
    while (window->poll(event))
    {
        auto consumed = imgui->process(event);
        if (consumed)
            continue;

        input.process(event);
        auto visitor = core::common::overload{
            [&](core::common::EventQuit&) {
                spdlog::info("Closing Client");
                window->close();
            },
            [](auto&&) {

            }
        };
        std::visit(visitor, event);
    }
}

void Game::update()
{
    imgui->update(*window);

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("FPS");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0 / static_cast<double>(ImGui::GetIO().Framerate), static_cast<double>(ImGui::GetIO().Framerate));
    ImGui::End();

    if (input.isKeyPressed(core::common::Key::F1))
        spdlog::info("F1 Pressed");

    if (input.isKeyPressed(core::common::Key::W))
        spdlog::info("W Pressed");

    if (input.isKeyDown(core::common::Key::W))
        spdlog::info("W Held");

    if (input.isKeyReleased(core::common::Key::W))
        spdlog::info("W Released");

    if (input.isMouseButtonReleased(core::common::Button::Left))
        spdlog::info("MB1 Released");
}

void Game::render()
{
    //todo: where should this live? in the renderer? do we need to use SDL to make the GL context current? can we use the GL API directly?
    SDL_GL_MakeCurrent(window_sdl->getRawWindow(), glc);

    // Clear the screen. todo: move to window (like SFML) or the renderer (GL specific?)
    meh::common::Library::clearColour(); //todo: not this :b
    glClear(GL_COLOR_BUFFER_BIT);

    // Adjust the viewport in case it is resized
    //todo: this is grabbing it from IMGUI, but we can just grab it from the window.
    //      have the renderer process window resize events or something? or does it need to be done exactly here?
    glViewport(0, 0, static_cast<int>(imgui->getRawIMGUI()->DisplaySize.x), static_cast<int>(imgui->getRawIMGUI()->DisplaySize.y));

    // Draw a triangle from the 3 vertices, underneath IMGUI
    //todo: renderer stuff innit
    glDrawArrays(GL_TRIANGLES, 0, 3);

    imgui->render();

    //todo: seems like window should do this, but then it's GL specific? so renderer?
    SDL_GL_SwapWindow(window_sdl->getRawWindow());
}
