#pragma once
#include "math.h"

namespace vgui
{
    struct Style
    {
        vec4f color;
        vec4f bg_color;
        vec4f borders;
        vec4f borders_color;
    };
    constexpr Style default_style = { {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f} };
}