#include "vgui/button.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Button::Button(vec4f rect)
{
    mi_rect = rect;
    //auto graphics_context = GraphicsDevice::getGraphicsContext();
}


void Button::setStyle(Style style)
{
    m_style = style;
}