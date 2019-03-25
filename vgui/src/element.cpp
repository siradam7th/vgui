#include "vgui/element.h"
using namespace vgui;

void Element::bindUIEvents(UIEvents events)
{
    m_uievents = events;
}

void Element::bindDrawEvents(DrawEvents events)
{
    m_drawevents = events;
}

const DrawEvents& Element::getDrawEvents() const
{
    return m_drawevents;
}

void Element::setRect(vec4f rect)
{
    mi_rect = rect;
}

const vec4f& Element::getRect() const
{
    return mi_rect;
}