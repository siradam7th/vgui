#include "vgui/checkbox.h"
#include "vgui/graphics_device.h"
using namespace vgui;

CheckBox::CheckBox(vec4f rect, bool checked, Style style) : m_checked(checked), m_style(style)
{
    mi_rect = rect;

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw background
        graphics_context->fillRectRounded(m_style.borders.x, mi_rect, m_style.bg_color);

        // draw foreground
        if (m_checked)
        {
            // calculate checkmark size
            constexpr float checkmark_checkbox_ratio = 0.5f;
            auto checkmark_size = vec2f{ mi_rect.z * checkmark_checkbox_ratio, mi_rect.w * checkmark_checkbox_ratio };
            // center checkmark inside the checkbox (X-axis and Y-axis)
            auto checkmark_rect = vec4f{ mi_rect.x, mi_rect.y, checkmark_size.x, checkmark_size.y };
            checkmark_rect.x = mi_rect.z * 0.5f - (checkmark_size.x * 0.5f) + mi_rect.x;
            checkmark_rect.y = mi_rect.w * 0.5f - (checkmark_size.y * 0.5f) + mi_rect.y;
            // draw checkmark
            graphics_context->fillRect(checkmark_rect, m_style.color);
        }
        
    };
    this->bindDrawEvents({ on_draw });
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