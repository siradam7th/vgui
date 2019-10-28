#include "textbox.h"
#include "vgui/graphics/graphics_device.h"
#include "vgui/elements/utility.h"
using namespace vgui;

constexpr float label_left_padding = 5.0f;

TextBox::TextBox(vec4f rect, UPtr<Label> label, Style style) : m_style(style), m_label(std::move(label))
{
    // setting the element is required for CanvasTree to function correctly
    setElement(this);

    m_rect = rect;
    auto on_draw = [this](IGraphicsContext* graphics_context)
    {
        // draw borders
        graphics_context->fillRectRounded(m_style.borders_radius, m_borders_rect, m_style.borders_color);

        // draw background
        graphics_context->fillRect(m_rect, m_style.bg_color);

        // draw foreground
        if (auto& on_draw = m_label->getDrawEvents().on_draw)
        {
            on_draw(graphics_context);
        }
    };

    auto on_update = [this]()
    {
        // center label inside the textbox (Y-axis only) and apply padding to the X-axis
        auto label_new_rect = utils::findCenterRectNoOverflow(m_rect, m_label->getRect());
        label_new_rect.x = m_rect.x + label_left_padding;
        m_label->setRect(label_new_rect);

        // calculate the borders rect
        // mapped as x: right, y: top, z: left, w: bottom 
        m_borders_rect = utils::findPaddedRect(m_rect, m_style.borders);
    };

    // issue the first update, this is important and mainly to avoid duplicating code
    on_update();
    this->bindDrawEvents({ on_draw, on_update });
}

void TextBox::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& TextBox::getDrawEvents()
{
    return m_draw_events;
}

void TextBox::bindUIEvents(UIEvents ui_events)
{
    m_ui_events = ui_events;
}

const UIEvents& TextBox::getUIEvents()
{
    return m_ui_events;
}

void TextBox::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& TextBox::getRect()
{
    return m_rect;
}