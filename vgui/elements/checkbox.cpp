#include "checkbox.h"
#include "vgui/graphics/graphics_device.h"
#include "vgui/elements/utility.h"
using namespace vgui;

constexpr float checkmark_checkbox_ratio = 0.5f;

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
            // draw checkmark
            graphics_context->fillRect(m_checkmark_rect, m_style.color);
        }
    };

    auto on_update = [this]() -> void
    {
        // calculate the checkmark rect
        m_checkmark_rect = utils::findCenterRectNoOverflow(m_rect,
            vec4f{
                0.0f, 0.0f,
                m_rect.z * checkmark_checkbox_ratio,
                m_rect.w * checkmark_checkbox_ratio
            });
    };

    // issue the first update, this is important and mainly to avoid duplicating code
    on_update();
    this->bindDrawEvents({ on_draw, on_update });
}

void CheckBox::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& CheckBox::getDrawEvents()
{
    return m_draw_events;
}

void CheckBox::bindUIEvents(UIEvents ui_events)
{
    m_ui_events = ui_events;
}

const UIEvents& CheckBox::getUIEvents()
{
    return m_ui_events;
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