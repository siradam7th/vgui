#pragma once
#include "vgui/common.h"
#include <functional>

namespace vgui
{
    enum MOUSE_EVENT_TYPE
    {
        MOUSE_EVENT_CLICK,
        MOUSE_EVENT_DBCLICK,
        MOUSE_EVENT_ENTER,
        MOUSE_EVENT_HOVER,
        MOUSE_EVENT_EXIT
    };

    struct UIEvents
    {
        std::function<void(const MOUSE_EVENT_TYPE event_type, i32 x, i32 y)> on_mouse_event;
    };
}