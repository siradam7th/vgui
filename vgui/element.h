#pragma once
#include "math.h"
#include "uievents.h"
#include "drawevents.h"
#include <functional>
namespace vgui
{
    class Element
    {
    public:
        void bindUIEvents(UIEvents events);
        void bindDrawEvents(DrawEvents events);
    protected:
        vec4f mi_rect;
    private:
        UIEvents m_uievents;
        DrawEvents m_drawevents;
    };
}