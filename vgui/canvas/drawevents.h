#pragma once
#include <functional>
#include "vgui/graphics/graphics_context.h"

namespace vgui
{
    struct DrawEvents
    {
        std::function<void(IGraphicsContext* graphics_context)> on_draw;
        // on_update: must be called when a change that affects the drawing of the element is made,
        // such as a change in the position of the element itself or its children.
        std::function<void()> on_update;
    };
}