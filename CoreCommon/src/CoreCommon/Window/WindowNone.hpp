#pragma once

//SELF
#include "CoreCommon/Window/Window.hpp"

//LIBS

//STD
#include <string>
#include <queue>

namespace core::common
{

class WindowNone final : public Window
{
public:
    explicit WindowNone(Window::Settings s);
    WindowNone(const WindowNone&) noexcept = delete;
    WindowNone(WindowNone&&) noexcept = delete;
    WindowNone& operator=(WindowNone&&) noexcept = delete;
    WindowNone& operator=(const WindowNone&) noexcept = delete;

    virtual bool poll(Event& event) final;
    virtual void send(Event event) final;

    [[nodiscard]] virtual bool isOpen() const final;
    [[nodiscard]] virtual bool isVerticalSyncEnabled() const final;

    [[nodiscard]] virtual unsigned int getWidth() const final;
    [[nodiscard]] virtual unsigned int getHeight() const final;

    virtual void init() final;
    virtual void close() final;
    virtual void clear(int r, int g, int b) final;
    virtual void display() final;

    virtual void setVerticalSyncEnabled(bool enabled) final;
    virtual void setWidth(unsigned int width) final;
    virtual void setHeight(unsigned int height) final;

    virtual bool setupRenderingContext(const meh::renderer::RenderContext& rc) final;

    static constexpr std::int32_t type_v = 1;

private:
    bool is_open = true;
    std::queue<Event> sent_events;
};

} // namespace core::common