#include "RendererGLES.hpp"

//SELF
#include "CoreCommon/Window/Window.hpp"
#include "CoreCommon/Renderer/GLES/RendererGLES.hpp"

//LIBS
#include <glad/glad.h>
#include <spdlog/spdlog.h>

//STD

using namespace core::common;

bool RendererGLES::init(Window& win)
{
    // Set up for GLES Rendering.
    // We can get context information for setup from the window itself if
    // we need it.
    RenderContext rc;
    rc.type = RENDERER_GLES;
    rc.versionMajor = 2;
    rc.versionMinor = 0;
    rc.rBits = 8;
    rc.gBits = 8;
    rc.bBits = 8;
    rc.aBits = 8;

    auto result = win.setupRenderingContext(rc);

    // Setup base pipeline settings.
    updateResolution(win.getWidth(), win.getHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return result;
}

void RendererGLES::updateResolution(int x, int y)
{
    glViewport(0, 0, x, y);
}

void RendererGLES::draw()
{
}

void RendererGLES::setCamera(Camera& camera)
{
    primaryCamera = &camera;
}

void RendererGLES::present()
{
    // TODO - Process the renderables and draw them to
    // the screen here.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!primaryCamera)
    {
        spdlog::error("RendererGLES: PrimaryCamera is not set. Screen will be blank.");
        return;
    }

    glm::mat4 lookat = primaryCamera->getLookAt();
    glm::mat4 persp = primaryCamera->getPerspective();

    // Here we need to bind these to the shaders we will use.
}
