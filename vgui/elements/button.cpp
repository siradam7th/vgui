#include "button.h"
#include "vgui/graphics/graphics_device.h"
#include "vgui/elements/utility.h"
using namespace vgui;

Button::Button(vec4f rect, UPtr<Label> label, Style style) : m_style(style), m_label(std::move(label))
{
    // setting the element is required for CanvasTree to function correctly
    setElement(this);

    m_rect = rect;
    auto on_draw = [this](IGraphicsContext* graphics_context)
    {
        // draw button background
        graphics_context->fillRectRounded(m_style.borders.x, m_rect, m_style.bg_color);

        // draw foreground
        if (auto& on_draw = m_label->getDrawEvents().on_draw)
        {
            on_draw(graphics_context);
        }
    };

    auto on_update = [this]()
    {
        // center the label inside the button
        m_label->setRect(utils::findCenterRectNoOverflow(m_rect, m_label->getRect()));
    };

    // issue the first update, this is important and mainly to avoid duplicating code
    on_update();
    this->bindDrawEvents({ on_draw, on_update });
}

void Button::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& Button::getDrawEvents()
{
    return m_draw_events;
}

void Button::bindUIEvents(UIEvents ui_events)
{
    m_ui_events = ui_events;
}

const UIEvents& Button::getUIEvents()
{
    return m_ui_events;
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