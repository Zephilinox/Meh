#include "Renderer/RendererBase.hpp"

namespace meh::renderer
{

class RendererGLES : public RendererBase
{
public:
    RendererGLES() = default;
    ~RendererGLES() = default;

    // Initialisation.
    bool init(meh::common::Window& win) override;

    // Settings Configuration
    void updateResolution(int x, int y) override;

    // RenderState Configuration.
    void draw() override;
    void setCamera(meh::scene::Camera& camera) override;

    // Update Screen. (This should only be avaliable to the core of the system.)
    void present() override;

private:
    meh::scene::Camera* primaryCamera = nullptr;
};

}
