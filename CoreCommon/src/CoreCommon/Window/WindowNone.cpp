#include "WindowNone.hpp"

//SELF

//LIBS

//STD

using namespace core::common;

WindowNone::WindowNone(Settings s)
    : Window(type_v, std::move(s))
{
}

unsigned int WindowNone::getWidth() const
{
    return settings.width;
}

unsigned int WindowNone::getHeight() const
{
    return settings.height;
}

bool WindowNone::poll(Event& event)
{
    if (sent_events.empty())
    {
        event = EventNone{};
        return false;
    }

    event = std::move(sent_events.front());
    sent_events.pop();
    return true;
}

void WindowNone::send(Event event)
{
    sent_events.push(std::move(event));
}

bool WindowNone::isOpen() const
{
    return is_open;
}

bool WindowNone::isVerticalSyncEnabled() const
{
    return settings.vsync;
}

void WindowNone::close()
{
    is_open = false;
}

void WindowNone::clear(int, int, int)
{
}

void WindowNone::display()
{
}

void WindowNone::setVerticalSyncEnabled(bool enabled)
{
    settings.vsync = enabled;
}

void WindowNone::setWidth(unsigned int width)
{
    settings.width = width;
}

void WindowNone::setHeight(unsigned int height)
{
    settings.height = height;
}