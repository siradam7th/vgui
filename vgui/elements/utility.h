#pragma once
#include "vgui/math.h"
#include <algorithm>

namespace vgui
{
    namespace utils
    {
        // find a rect that fits in the middle of the parent rect, if the child rect
        // is larger than the parent, the axis that overflow will be clamped to be
        // only as large as the parent axis is.
        static inline constexpr vec4f findCenterRectNoOverflow(vec4f parent, vec4f child)
        {
            vec4f res;
            res.z = std::min(child.z, parent.z);
            res.w = std::min(child.w, parent.w);
            res.x = (parent.z * 0.5f) - (res.z * 0.5f) + parent.x;
            res.y = (parent.w * 0.5f) - (res.w * 0.5f) + parent.y;
            return res;
        }

        // find a rect that fits in the middle of the parent rect, if the child rect
        // is larger than the parent, allow overflow on that axis.
        static inline constexpr vec4f findCenterRectOverflow(vec4f parent, vec4f child)
        {
            return vec4f
            {
                (parent.z * 0.5f) - (child.z * 0.5f) + parent.x,
                (parent.w * 0.5f) - (child.w * 0.5f) + parent.y,
                child.z,
                child.w
            };
        }

        // find a rect that extends or shrinks the reference rect based on the padding values on each sides,
        // where padding values are mapped to (x: right, y: top, z: left, w: bottom) sides.
        static inline constexpr vec4f findPaddedRect(vec4f reference_rect, vec4f padding)
        {
            vec4f padded_rect;
            // calculate right and left borders:
            // add right border
            padded_rect.x = reference_rect.x + padding.x;
            // add left border by subtracting from the result of the right border addition
            // this is where we handle having both right and left borders set at the same time
            // or just one of them is set, and the other is 0.0f
            padded_rect.x = padded_rect.x - (padding.z + padding.x);
            // scale the width of the rect to be large enough for both left and right borders
            padded_rect.z = reference_rect.z + padding.z + padding.x;

            // calculate top and bottom borders:
            // add bottom border
            padded_rect.y = reference_rect.y + padding.w;
            // add top border by subtracting from the result of the bottom border addition
            // this is where we handle having both top and bottom borders set at the same time
            // or just one of them is set, and the other is 0.0f
            padded_rect.y = padded_rect.y - (padding.y + padding.w);
            // scale the height of the rect to be large enough for both top and bottom borders
            padded_rect.w = reference_rect.w + padding.w + padding.y;
            return padded_rect;
        }
    }
}