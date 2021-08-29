#pragma once

//SELF
#include "CommonLib/Window/Window.hpp"

//LIBS

//STD
#include <string>

struct SDL_Window;

namespace meh::common
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

    //virtual bool poll(Event& e) final;
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

    static constexpr std::int32_t type_v = 1;

private:
    bool is_open = true;
    SDL_Window* raw_window;
};

} // namespace meh::common