#include "spdlog/spdlog.h"
#include "WindowSDL.hpp"

//SELF

//LIBS
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <cstring> //memcpy for SDL
    #include <SDL.h>

    #define GL_GLEXT_PROTOTYPES 1
    #include <SDL_opengles2.h>
#else
    #include <cstring> //memcpy for SDL
    #include <SDL.h>
#endif

//STD

using namespace meh::common;

WindowSDL::WindowSDL(Settings s)
    : Window(type_v, std::move(s))
{}

WindowSDL::~WindowSDL() noexcept
{
    SDL_DestroyWindow(raw_window);
}

unsigned int WindowSDL::getWidth() const
{
    return settings.width;
}

unsigned int WindowSDL::getHeight() const
{
    return settings.height;
}

bool WindowSDL::isOpen() const
{
    //return window.isOpen();
    return is_open;
}

bool WindowSDL::isVerticalSyncEnabled() const
{
    return settings.vsync;
}

void WindowSDL::init()
{
    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    raw_window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        static_cast<int>(settings.width), static_cast<int>(settings.height), window_flags);
}

void WindowSDL::close()
{
    //window.close();
    is_open = false;
}

void WindowSDL::clear(int, int, int)
{
    //window.clear({static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), static_cast<std::uint8_t>(b), 255});
}

void WindowSDL::display()
{
    //window.display();
}

void WindowSDL::setVerticalSyncEnabled(bool enabled)
{
    settings.vsync = enabled;
    //window.setVerticalSyncEnabled(enabled);
}

void WindowSDL::setWidth(unsigned int width)
{
    settings.width = width;
    //window.setSize({properties.height, properties.width});
}

void WindowSDL::setHeight(unsigned int height)
{
    settings.height = height;
    //window.setSize({properties.height, properties.width});
}

bool WindowSDL::setupRenderingContext(const meh::renderer::RenderContext& rc)
{
    // What profile are we using.
    bool noError = true;
    SDL_GLprofile profile = SDL_GL_CONTEXT_PROFILE_CORE;

    switch (rc.type) {
    case renderer::RendererType::RENDERER_GLES:
        profile = SDL_GL_CONTEXT_PROFILE_ES;
        break;
    default:
        spdlog::error("WindowSDL: RenderContext not recognised. Aborting.");
        return false;
    }

    noError = noError && SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, rc.versionMajor);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, rc.versionMinor);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Display settings.
    noError = noError && SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rc.rBits);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rc.gBits);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rc.bBits);
    noError = noError && SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, rc.aBits);
    return noError;
}

SDL_Window* WindowSDL::getRawWindow() const
{
    return raw_window;
}
