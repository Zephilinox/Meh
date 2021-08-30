#include "WindowSDL.hpp"

//SELF
#include <CommonLib/Input/KeysSDL.hpp>

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

#include <spdlog/spdlog.h>

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

bool WindowSDL::poll(Event& event)
{
    if (!sent_events.empty())
    {
        event = std::move(sent_events.front());
        sent_events.pop();
        return true;
    }

    SDL_Event sdl_event;
    const auto found_event = SDL_PollEvent(&sdl_event) != 0;
    event = EventNone{};
    if (!found_event)
        return false;

    switch (sdl_event.type)
    {
    case SDL_QUIT:
    {
        spdlog::info("App is quitting");
        event = EventQuit{};
        break;
    }
    case SDL_APP_TERMINATING:
    {
        spdlog::info("App is terminating");
        break;
    }
    case SDL_APP_LOWMEMORY:
    {
        spdlog::info("App is low on memory");
        break;
    }
    case SDL_APP_WILLENTERBACKGROUND:
    {
        spdlog::info("App is entering background");
        break;
    }
    case SDL_APP_DIDENTERBACKGROUND:
    {
        spdlog::info("App entered background");
        break;
    }
    case SDL_APP_WILLENTERFOREGROUND:
    {
        spdlog::info("App is entering foreground");
        break;
    }
    case SDL_APP_DIDENTERFOREGROUND:
    {
        spdlog::info("App entered foreground");
        break;
    }
    case SDL_WINDOWEVENT:
    {
        auto& window_event = sdl_event.window;

        switch (window_event.event)
        {
        case SDL_WINDOWEVENT_SHOWN:
        {
            //spdlog::info("Window {} shown", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Shown };
            break;
        }
        case SDL_WINDOWEVENT_HIDDEN:
        {
            //spdlog::info("Window {} hidden", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Hidden };
            break;
        }
        case SDL_WINDOWEVENT_EXPOSED:
        {
            //spdlog::info("Window {} exposed", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Exposed };
            break;
        }
        case SDL_WINDOWEVENT_MOVED:
        {
            spdlog::info("Window {} moved to {},{}",
                         window_event.windowID, window_event.data1, window_event.data2);
            break;
        }
        case SDL_WINDOWEVENT_RESIZED:
        {
            spdlog::info("Window {} resized to {},{}",
                         window_event.windowID, window_event.data1, window_event.data2);
            break;
        }
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
            spdlog::info("Window {} size changed to {},{}",
                         window_event.windowID, window_event.data1, window_event.data2);
            break;
        }
        case SDL_WINDOWEVENT_MINIMIZED:
        {
            //spdlog::info("Window {} minimized", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Minimized };
            break;
        }
        case SDL_WINDOWEVENT_MAXIMIZED:
        {
            //spdlog::info("Window {} maximized", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Maximized };
            break;
        }
        case SDL_WINDOWEVENT_RESTORED:
        {
            //spdlog::info("Window {} restored", window_event.windowID);
            event = EventVisibility{ EventVisibility::Visibility::Restored };
            break;
        }
        case SDL_WINDOWEVENT_ENTER:
        {
            //spdlog::info("Mouse entered window {}", window_event.windowID);
            event = EventMouseEnter{ true };
            break;
        }
        case SDL_WINDOWEVENT_LEAVE:
        {
            //spdlog::info("Mouse left window {}", window_event.windowID);
            event = EventMouseEnter{ false };
            break;
        }
        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
            //spdlog::info("Window {} gained keyboard focus", window_event.windowID);
            event = EventFocus{ true };
            break;
        }
        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
            //spdlog::info("Window {} lost keyboard focus", window_event.windowID);
            event = EventFocus{ false };
            break;
        }
        case SDL_WINDOWEVENT_CLOSE:
        {
            //spdlog::info("Window {} closed", window_event.windowID);
            event = EventClose();
            break;
        }
        case SDL_WINDOWEVENT_TAKE_FOCUS:
        {
            spdlog::info("Window {} is offered a focus", window_event.windowID);
            break;
        }
        case SDL_WINDOWEVENT_HIT_TEST:
        {
            spdlog::info("Window {} has a special hit test", window_event.windowID);
            break;
        }
        default:
        {
            spdlog::info("Window {} received an unknown event", window_event.windowID);
            break;
        }
        }
        break;
    }
    case SDL_SYSWMEVENT:
    {
        spdlog::info("SysWMEvent");
        break;
    }
    case SDL_KEYDOWN:
    {
        /*spdlog::info("Keydown {} {}",
                SDL_GetScancodeName(sdl_event.key.keysym.scancode), SDL_GetKeyName(sdl_event.key.keysym.sym));*/
        event = EventKey{ SDLKeyConversion(sdl_event.key.keysym.sym), true, static_cast<std::int32_t>(sdl_event.key.keysym.scancode) };
        break;
    }
    case SDL_KEYUP:
    {
        /*spdlog::info("Keyup {} {}",
                SDL_GetScancodeName(sdl_event.key.keysym.scancode), SDL_GetKeyName(sdl_event.key.keysym.sym));*/
        event = EventKey{ SDLKeyConversion(sdl_event.key.keysym.sym), false, static_cast<std::int32_t>(sdl_event.key.keysym.scancode) };
        break;
    }
    case SDL_TEXTEDITING:
    {
        spdlog::info("In window {}, editing text {}, with a start of {} and a length of {}",
                     sdl_event.edit.windowID,
                     sdl_event.edit.text,
                     sdl_event.edit.start,
                     sdl_event.edit.length);
        break;
    }
    case SDL_TEXTINPUT:
    {
        spdlog::info("In window {}, inputing text {}",
                     sdl_event.edit.windowID,
                     sdl_event.edit.text);
        break;
    }
    case SDL_KEYMAPCHANGED:
    {
        spdlog::info("Keymap Changed");
        break;
    }
    case SDL_MOUSEMOTION:
    {
        /*spdlog::info("In window {}, mouse {} moved from {}, {} to {}, {}\nM1={}, M2={}, M3={}, M4={}, M5={}",
                sdl_event.motion.windowID,
                sdl_event.motion.which,
                sdl_event.motion.x - sdl_event.motion.xrel,
                sdl_event.motion.y - sdl_event.motion.yrel,
                sdl_event.motion.x,
                sdl_event.motion.y,
                sdl_event.motion.state & SDL_BUTTON_LMASK,
                sdl_event.motion.state & SDL_BUTTON_RMASK,
                sdl_event.motion.state & SDL_BUTTON_MMASK,
                sdl_event.motion.state & SDL_BUTTON_X1MASK,
                sdl_event.motion.state & SDL_BUTTON_X2MASK);*/
        event = EventMouseMove{ sdl_event.motion.x, sdl_event.motion.y, sdl_event.motion.xrel, sdl_event.motion.yrel };
        break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
        /*spdlog::info("In window {}, mouse {} is down at {}, {}\nclicks={} button={}",
                sdl_event.button.windowID, sdl_event.button.which, sdl_event.button.x, sdl_event.button.y,
                sdl_event.button.clicks, sdl_event.button.button);*/
        event = EventMouseButton{ SDLButtonConversion(sdl_event.button.button), true, sdl_event.button.x, sdl_event.button.y };
        break;
    }
    case SDL_MOUSEBUTTONUP:
    {
        /*spdlog::info("In window {}, mouse {} is up at {}, {}\nclicks={} button={}",
                sdl_event.button.windowID, sdl_event.button.which, sdl_event.button.x, sdl_event.button.y,
                sdl_event.button.clicks, sdl_event.button.button);*/
        event = EventMouseButton{ SDLButtonConversion(sdl_event.button.button), false, sdl_event.button.x, sdl_event.button.y };
        break;
    }
    case SDL_MOUSEWHEEL:
    {
        /*spdlog::info("In window {}, mousewheel {} scrolled {},{} ({})",
                     sdl_event.wheel.windowID,
                     sdl_event.wheel.which,
                     sdl_event.wheel.x,
                     sdl_event.wheel.y,
                     sdl_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? "normal" : "inverted");*/

        if (sdl_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
            event = EventMouseWheel{ sdl_event.wheel.x, sdl_event.wheel.y };
        else
            event = EventMouseWheel{ sdl_event.wheel.y, sdl_event.wheel.x };

        break;
    }
    case SDL_CLIPBOARDUPDATE:
    {
        spdlog::info("clipboard has changed");
        break;
    }
    case SDL_DROPFILE:
    {
        spdlog::info("File {} drop on window {}", sdl_event.drop.windowID, sdl_event.drop.file);
        SDL_free(sdl_event.drop.file);
        break;
    }
    case SDL_DROPTEXT:
    {
        spdlog::info("Text {} drop on window {}", sdl_event.drop.windowID, sdl_event.drop.file);
        SDL_free(sdl_event.drop.file);
        break;
    }
    case SDL_DROPBEGIN:
    {
        spdlog::info("File {} drop on window {} begun", sdl_event.drop.windowID, sdl_event.drop.file);
        SDL_free(sdl_event.drop.file);
        break;
    }
    case SDL_DROPCOMPLETE:
    {
        spdlog::info("File {} drop on window {} completed", sdl_event.drop.windowID, sdl_event.drop.file);
        SDL_free(sdl_event.drop.file);
        break;
    }
    case SDL_AUDIODEVICEADDED:
    {
        spdlog::info("Audio Device {} added. iscapture={}", sdl_event.adevice.which, sdl_event.adevice.iscapture);
        break;
    }
    case SDL_AUDIODEVICEREMOVED:
    {
        spdlog::info("Audio Device {} removed. iscapture={}", sdl_event.adevice.which, sdl_event.adevice.iscapture);
        break;
    }
    case SDL_RENDER_TARGETS_RESET:
    {
        spdlog::info("Render Target Reset");
        break;
    }
    case SDL_RENDER_DEVICE_RESET:
    {
        spdlog::info("Render Device Reset");
        break;
    }
    case SDL_USEREVENT:
    {
        spdlog::info("UserEvent");
        break;
    }
    case SDL_LASTEVENT:
    {
        spdlog::info("Unreachable");
        break;
    }
    default:
    {
        spdlog::info("sdl_event type of {}: was it a joystick/controller/finger gestures event?", sdl_event.type);
        break;
    }
    }

    return found_event;
}

void WindowSDL::send(Event event)
{
    sent_events.push(std::move(event));
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
