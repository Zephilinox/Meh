#pragma once

#include "CommonLib/Renderer/RendererData.hpp"

namespace meh::common
{
    class Window;
}

namespace meh::renderer
{

class RendererBase {
public:
    RendererBase() = default;
    virtual ~RendererBase() = default;

    // Initialisation.
    virtual bool init(meh::common::Window& win) = 0;

    // Settings Configuration
    virtual void updateResolution(int x, int y) = 0;

    // RenderState Configuration.
    virtual void draw() = 0;
    virtual void setCamera() = 0;

    // Update Screen. (This should only be avaliable to the core of the system.)
    virtual void present() = 0;
};

}