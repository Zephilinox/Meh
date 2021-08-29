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
{
    auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    raw_window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(settings.width), static_cast<int>(settings.height), window_flags);
}

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

SDL_Window* WindowSDL::getRawWindow() const
{
    return raw_window;
}
