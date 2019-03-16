#pragma once
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
    private:
        UIEvents m_uievents;
        DrawEvents m_drawevents;
    };
}