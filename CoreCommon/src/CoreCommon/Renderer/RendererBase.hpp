#pragma once

//SELF
#include "CoreCommon/Renderer/RendererData.hpp"
#include "CoreCommon/Camera/Camera.hpp"

//LIBS

//STD

namespace core::common
{

class Window;

class RendererBase
{
public:
    RendererBase() = default;
    virtual ~RendererBase() = default;

    // Initialisation.
    virtual bool init(Window& win) = 0;

    // Settings Configuration
    virtual void updateResolution(int x, int y) = 0;

    // RenderState Configuration.
    virtual void draw() = 0;
    virtual void setCamera(Camera& camera) = 0;

    // Update Screen. (This should only be avaliable to the core of the system.)
    virtual void present() = 0;
};

} // namespace core::common