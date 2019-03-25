#include "vgui/button.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Button::Button(vec4f rect, Style style) : m_style(style)
{
    mi_rect = rect;
    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw button background
        graphics_context->fillRectRounded(m_style.borders.x, mi_rect, m_style.bg_color);
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