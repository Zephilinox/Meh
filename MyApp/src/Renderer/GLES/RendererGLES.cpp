#include <glad/glad.h>
#include "CommonLib/Window/Window.hpp"

#include "Renderer/GLES/RendererGLES.hpp"

bool meh::renderer::RendererGLES::init(meh::common::Window& win)
{
    // Set up for GLES Rendering.
    // We can get context information for setup from the window itself if
    // we need it.
    RenderContext rc;
    rc.type = RENDERER_GLES;
    rc.versionMajor = 2;
    rc.versionMinor = 0;
    rc.rBits = 8; rc.gBits = 8;
    rc.bBits = 8; rc.aBits = 8;

    auto result = win.setupRenderingContext(rc);

    // Setup base pipeline settings.
    updateResolution(win.getWidth(), win.getHeight());

    return result;
}

void meh::renderer::RendererGLES::updateResolution(int x, int y)
{
    glViewport(0, 0, x, y);
}

void meh::renderer::RendererGLES::draw()
{

}

void meh::renderer::RendererGLES::setCamera()
{

}

void meh::renderer::RendererGLES::present()
{

}
