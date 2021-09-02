#pragma once

//SELF
#include "CoreCommon/Window/Window.hpp"

//LIBS

//STD
#include <string>
#include <queue>

struct SDL_Window;

namespace core::common
{

class WindowSDL final : public Window
{
public:
    explicit WindowSDL(Window::Settings s);
    WindowSDL(const WindowSDL&) noexcept = delete;
    WindowSDL(WindowSDL&&) noexcept = delete;
    WindowSDL& operator=(WindowSDL&&) noexcept = delete;
    WindowSDL& operator=(const WindowSDL&) noexcept = delete;
    ~WindowSDL() noexcept final;

    virtual bool poll(Event& event) final;
    virtual void send(Event event) final;

    [[nodiscard]] virtual bool isOpen() const final;
    [[nodiscard]] virtual bool isVerticalSyncEnabled() const final;

    [[nodiscard]] virtual unsigned int getWidth() const final;
    [[nodiscard]] virtual unsigned int getHeight() const final;

    virtual void close() final;
    virtual void clear(int r, int g, int b) final;
    virtual void display() final;

    virtual void setVerticalSyncEnabled(bool enabled) final;
    virtual void setWidth(unsigned int width) final;
    virtual void setHeight(unsigned int height) final;

    SDL_Window* getRawWindow() const;

    static constexpr std::int32_t type_v = 2;

private:
    bool is_open = true;
    SDL_Window* raw_window;
    std::queue<Event> sent_events;
};

} // namespace core::common