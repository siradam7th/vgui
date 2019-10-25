#include "textbox.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

TextBox::TextBox(vec4f rect, UPtr<Label> label, Style style) : m_style(style), m_label(std::move(label))
{
    // setting the element is required for CanvasTree to function correctly
    setElement(this);

    m_rect = rect;
    auto label_rect = m_label->getRect();
    // center label inside the textbox (Y-axis only)
    auto label_new_rect = vec4f{ m_rect.x, m_rect.y, label_rect.z, label_rect.w };
    label_new_rect.x = m_rect.x + 5.0f; //TODO: replace this value with Style.padding once implemented
    label_new_rect.y = m_rect.w * 0.5f - (label_rect.w * 0.5f) + m_rect.y;
    m_label->setRect(label_new_rect);

    auto on_draw = [this](IGraphicsContext* graphics_context)
    {
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
        // center label inside the textbox (Y-axis only)
        auto label_rect = m_label->getRect();
        auto label_new_rect = vec4f{ m_rect.x, m_rect.y, label_rect.z, label_rect.w };
        label_new_rect.x = m_rect.x + 5.0f;
        label_new_rect.y = m_rect.w * 0.5f - (label_rect.w * 0.5f) + m_rect.y;
        m_label->setRect(label_new_rect);
    };
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

void TextBox::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& TextBox::getRect()
{
    return m_rect;
}