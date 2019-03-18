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