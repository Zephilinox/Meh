#pragma once

//SELF

//LIBS

//STD
#include <cstdint>

namespace core::common
{

class RenderableBase
{
public:
    RenderableBase() = default;
    virtual ~RenderableBase() = default;

    // This contains core routienes for retrieving
    // Rendering data for drawing.

    virtual uint8_t* vertexBuffer() = 0;
    virtual uint8_t* indexBuffer() = 0;
};

} // namespace core::common