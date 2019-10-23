#pragma once
#include <functional>
#include "vgui/graphics/graphics_context.h"

namespace vgui
{
    struct DrawEvents
    {
        std::function<void(IGraphicsContext* graphics_context)> on_draw;
    };
}