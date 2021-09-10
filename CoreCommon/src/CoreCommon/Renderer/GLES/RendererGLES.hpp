#pragma once

//SELF
#include "CoreCommon/Renderer/RendererBase.hpp"
#include "CoreCommon/Camera/Camera.hpp"

//LIBS

//STD

namespace core::common
{

class RendererGLES : public RendererBase
{
public:
    RendererGLES() = default;
    ~RendererGLES() = default;

    // Initialisation.
    bool init(Window& win) override;

    // Settings Configuration
    void updateResolution(int x, int y) override;

    // RenderState Configuration.
    void draw() override;
    void setCamera(Camera& camera) override;

    // Update Screen. (This should only be avaliable to the core of the system.)
    void present() override;

private:
    Camera* primaryCamera = nullptr;
};

} // namespace core::common
