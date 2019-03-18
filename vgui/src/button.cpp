#include "vgui/button.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Button::Button(vec4f rect, Style style) : m_style(style)
{
    mi_rect = rect;
    auto on_draw = [&style = m_style, &rect = mi_rect]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw button background
        graphics_context->drawRoundedRect(style.borders.x, rect, style.bg_color);
    };
    this->bindDrawEvents({ on_draw });
}


void Button::setStyle(Style style)
{
    m_style = style;
}

Style& Button::getStyle()
{
    return m_style;
}