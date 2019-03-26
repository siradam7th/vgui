#include "vgui/button.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Button::Button(vec4f rect, UPtr<Label> label, Style style) : m_style(style), m_label(std::move(label))
{
    mi_rect = rect;
    auto label_rect = m_label->getRect();
    // center label inside the button (X-axis and Y-axis)
    auto label_new_rect = vec4f{ mi_rect.x, mi_rect.y, label_rect.z, label_rect.w };
    label_new_rect.x = mi_rect.z * 0.5f - (label_rect.z * 0.5f) + mi_rect.x;
    label_new_rect.y = mi_rect.w * 0.5f - (label_rect.w * 0.5f) + mi_rect.y;
    m_label->setRect(label_new_rect);

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw button background
        graphics_context->fillRectRounded(m_style.borders.x, mi_rect, m_style.bg_color);

        // draw foreground
        if (auto& on_draw = m_label->getDrawEvents().on_draw)
        {
            on_draw();
        }
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

Label& Button::getLabel()
{
    return *m_label;
}