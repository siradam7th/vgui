#include "vgui/button.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Button::Button(vec4f rect, UPtr<Label> label, Style style) : m_style(style), m_label(std::move(label))
{
    m_rect = rect;
    auto label_rect = m_label->getRect();
    // center label inside the button (X-axis and Y-axis)
    auto label_new_rect = vec4f{ m_rect.x, m_rect.y, label_rect.z, label_rect.w };
    label_new_rect.x = m_rect.z * 0.5f - (label_rect.z * 0.5f) + m_rect.x;
    label_new_rect.y = m_rect.w * 0.5f - (label_rect.w * 0.5f) + m_rect.y;
    m_label->setRect(label_new_rect);

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw button background
        graphics_context->fillRectRounded(m_style.borders.x, m_rect, m_style.bg_color);

        // draw foreground
        if (auto& on_draw = m_label->getDrawEvents().on_draw)
        {
            on_draw();
        }
    };
    this->bindDrawEvents({ on_draw });
}

void Button::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& Button::getDrawEvents()
{
    return m_draw_events;
}

void Button::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& Button::getRect()
{
    return m_rect;
}

void Button::setStyle(Style style)
{
    m_style = style;
}

Style& Button::getStyle()
{
    return m_style;
}

Label* const Button::getLabel()
{
    return m_label.get();
}