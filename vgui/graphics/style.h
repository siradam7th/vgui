#pragma once
#include "vgui/math.h"

namespace vgui
{
    struct Style
    {
        // set foreground color
        vec4f color;
        // set background color
        vec4f bg_color;
        // set every single border value (x: right, y: top, z: left, w: bottom)
        vec4f borders;
        // set the color of all the borders (same for all sides)
        vec4f borders_color;
        // set the border radius of all the borders (same for all sides)
        float borders_radius;
    };
	
    constexpr Style default_style = {
        { 1.0f, 1.0f, 1.0f, 1.0f }, // color
        { 0.0f, 0.0f, 0.0f, 1.0f }, // bg_color
        { 0.0f, 0.0f, 0.0f, 0.0f }, // borders
        { 0.0f, 0.0f, 0.0f, 0.0f }, // borders_color
        0.0f //border_radius
    };
}