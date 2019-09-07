#include "slider.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

#include <algorithm> // for std::min & std::max

Slider::Slider(vec4f rect, float value, Style style) : m_style(style), m_value(value)
{
    m_rect = rect;

    // defines the knob size to slider size ratio
    constexpr float slider_knob_ratio = 1.5f;

    // the knob is a square so the same ratio is applied to both the width and height
    auto knob_size = vec2f((m_rect.w * slider_knob_ratio), (m_rect.w * slider_knob_ratio));
    m_knob_rect = calcKnobRect(value, knob_size);

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();

        // draw background
        graphics_context->fillRect(m_rect, m_style.bg_color);

        // draw foreground
        graphics_context->fillRectRounded(m_style.borders.x, m_knob_rect, m_style.color);
    };
    this->bindDrawEvents({ on_draw });
}

void Slider::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& Slider::getDrawEvents()
{
    return m_draw_events;
}

void Slider::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& Slider::getRect()
{
    return m_rect;
}

vec4f Slider::calcKnobRect(float value, vec2f knob_rect_size)
{
    return vec4f
    {
        m_rect.x + ((m_rect.z - knob_rect_size.y) *  value),
        m_rect.y + (m_rect.w * 0.5f) - (knob_rect_size.y * 0.5f),
        knob_rect_size.x,
        knob_rect_size.y
    };
}

void Slider::setValue(float value)
{
    // cap the value between 0.0f and 1.0f
    float cap_val = std::min(1.0f, value);
    float current_val = std::max(0.0f, cap_val);

    if (m_value != current_val)
    {
        // update internal value
        m_value = current_val;
        // recalculate the knob rect
        m_knob_rect = calcKnobRect(current_val, { m_knob_rect.z, m_knob_rect.w });
    }
}

void Slider::setStyle(Style style)
{
    m_style = style;
}

float Slider::getValue() const
{
    return m_value;
}

Style& Slider::getStyle()
{
    return m_style;
}
