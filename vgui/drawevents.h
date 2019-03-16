#pragma once
#include <functional>

namespace vgui
{
    struct DrawEvents
    {
        std::function<void()> on_draw;
    };
}