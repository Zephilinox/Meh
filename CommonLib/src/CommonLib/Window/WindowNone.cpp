#include "WindowNone.hpp"

//SELF

//LIBS

//STD

using namespace meh::common;

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

bool WindowNone::isOpen() const
{
    return is_open;
}

bool WindowNone::isVerticalSyncEnabled() const
{
    return settings.vsync;
}

void WindowNone::init()
{
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

bool WindowNone::setupRenderingContext(const meh::renderer::RenderContext& rc)
{
    return true;
}
