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
    }
}