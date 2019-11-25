#pragma once
#include "vgui/math.h"

namespace vgui
{
    enum FLEXBOX_FLEX_WRAP
    {
        FLEX_WRAP,
        FLEX_NOWRAP,
        FLEX_WRAP_REVERSE
    };

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

        // flexbox properties
        FLEXBOX_FLEX_WRAP flex_wrap;
        // flexbox item properties
        int flex_grow;
        int flex_shrink;
    };
	
    constexpr Style default_style = {
        { 1.0f, 1.0f, 1.0f, 1.0f }, // color
        { 0.0f, 0.0f, 0.0f, 1.0f }, // bg_color
        { 0.0f, 0.0f, 0.0f, 0.0f }, // borders
        { 0.0f, 0.0f, 0.0f, 0.0f }, // borders_color
        0.0f, //border_radius
        // flexbox properties
        FLEX_NOWRAP,                // flex_wrap
        0, 0                        // flex_grow, flex_shrink
    };
}