#include "checkbox.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

CheckBox::CheckBox(vec4f rect, bool checked, Style style) : m_checked(checked), m_style(style)
{
    // setting the element is required for CanvasTree to function correctly
    setElement(this);

    m_rect = rect;
    auto on_draw = [this](IGraphicsContext* graphics_context)
    {
        // draw background
        graphics_context->fillRectRounded(m_style.borders.x, m_rect, m_style.bg_color);

        // draw foreground
        if (m_checked)
        {
            // calculate checkmark size
            constexpr float checkmark_checkbox_ratio = 0.5f;
            auto checkmark_size = vec2f{ m_rect.z * checkmark_checkbox_ratio, m_rect.w * checkmark_checkbox_ratio };
            // center checkmark inside the checkbox (X-axis and Y-axis)
            auto checkmark_rect = vec4f{ m_rect.x, m_rect.y, checkmark_size.x, checkmark_size.y };
            checkmark_rect.x = m_rect.z * 0.5f - (checkmark_size.x * 0.5f) + m_rect.x;
            checkmark_rect.y = m_rect.w * 0.5f - (checkmark_size.y * 0.5f) + m_rect.y;
            // draw checkmark
            graphics_context->fillRect(checkmark_rect, m_style.color);
        }
        
    };
    this->bindDrawEvents({ on_draw });
}

void CheckBox::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& CheckBox::getDrawEvents()
{
    return m_draw_events;
}

void CheckBox::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& CheckBox::getRect()
{
    return m_rect;
}

bool CheckBox::isChecked()
{
    return m_checked;
}

bool CheckBox::toggle()
{
    m_checked = !m_checked;
    return m_checked;
}

void CheckBox::setStyle(Style style)
{
    m_style = style;
}

Style& CheckBox::getStyle()
{
    return m_style;
}