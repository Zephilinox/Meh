#pragma once

//SELF

//LIBS

//STD

namespace core::common
{

enum RendererType
{
    RENDERER_GLES = 0,
    RENDERER_GL,
    RENDERER_VK,
};

// RenderContext settings. (Sent to window for setup)
// TODO - Do we need flags for antialiasing and debugging.
struct RenderContext
{
    RendererType type;
    int versionMajor = 0;
    int versionMinor = 0;
    int rBits = 8, gBits = 8;
    int bBits = 8, aBits = 8;
};

} // namespace core::common