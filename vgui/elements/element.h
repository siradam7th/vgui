#pragma once
#include "vgui/math.h"
#include "vgui/canvas/uievents.h"
#include "vgui/canvas/drawevents.h"

namespace vgui
{
    class Element
    {
    public:
        virtual void bindUIEvents(UIEvents events) = 0;
        virtual const UIEvents& getUIEvents() = 0;
        virtual void bindDrawEvents(DrawEvents events) = 0;
        virtual const DrawEvents& getDrawEvents() = 0;
        virtual void setRect(vec4f rect) = 0;
        virtual const vec4f& getRect() = 0;
        virtual ~Element() = default;
    };
}