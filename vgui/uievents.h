#pragma once
#include <functional>

namespace vgui
{
    struct UIEvents
    {
        std::function<void()> on_mouse_enter;
        std::function<void()> on_mouse_exit;
        std::function<void()> on_mouse_hover;
    };
}