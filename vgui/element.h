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
        const DrawEvents& getDrawEvents() const;
        void setRect(vec4f rect);
        const vec4f& getRect() const;
    protected:
        vec4f mi_rect;
    private:
        UIEvents m_uievents;
        DrawEvents m_drawevents;
    };
}