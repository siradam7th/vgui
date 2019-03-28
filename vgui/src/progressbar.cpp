#include "vgui/progressbar.h"
#include "vgui/graphics_device.h"
using namespace vgui;

#include <charconv>     // for std::to_chars
#include <cmath>        // for std::round
#include <algorithm>    // for std::min

ProgressBar::ProgressBar(vec4f rect, float value, Style style, const std::string& font_name, vec4f label_color)
    : m_value(value), m_style(style), m_label(std::make_unique<Label>("", font_name, vec2f{ 0.0f, 0.0f }))
{
    mi_rect = rect;

    m_label->setFontName(font_name);
    m_label->getStyle().color = label_color;
    m_label->setText(toPercentage(value).value_or("%"));

    // calculate the progress rect
    m_progress_rect = calcProgressRect(value);

    // center label inside the progress rect (X-axis and Y-axis)
    auto label_rect = m_label->getRect();
    vec4f label_new_rect{ 0.0f, 0.0f, label_rect.z, label_rect.w };
    label_new_rect.x = mi_rect.x + (mi_rect.z * 0.5f) - (label_rect.z * 0.5f);
    label_new_rect.y = mi_rect.y + (mi_rect.w * 0.5f) - (label_rect.w * 0.5f);
    m_label->setRect(label_new_rect);

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        // draw background
        graphics_context->fillRect(mi_rect, m_style.bg_color);

        // draw foreground
        graphics_context->fillRect(m_progress_rect, m_style.color);

        // draw label
        if (auto& label_on_draw = m_label->getDrawEvents().on_draw)
        {
            label_on_draw();
        }

    };
    this->bindDrawEvents({ on_draw });
}

vec4f ProgressBar::calcProgressRect(float value)
{
    // TODO: replace with style.padding once implemented
    constexpr vec2f padding = { 2.0f, 2.0f };

    // std::max the X-axis size calculation to prevent rect overflow and underflow
    auto progress_rect_size = vec2f
    { 
        std::max(0.0f, mi_rect.z * m_value - padding.x),
        mi_rect.w - padding.y
    };

    return vec4f
    {
        mi_rect.x + padding.x,
        mi_rect.y + padding.y,
        std::max(0.0f, progress_rect_size.x - padding.x),
        progress_rect_size.y - padding.y 
    };
}

// find the text representation of the provided float value,
// 'value' is expected to be in the 0-1 range
std::optional<std::string> ProgressBar::toPercentage(float value)
{
    // cap the percentage between 0 and 100
    if (value >= 1.0f)
        return { "100%" };
    if (value <= 0.0f)
        return { "0%" };

    char char_value[4] = { 0 };
    // multiply by 100 to make it in 0-100 range instead of 0-1 before to_chars() conversion
    // then round to avoid 'result_out_of_range' because the float might convert to more than 3 digits
    auto val = std::round(value * 100.0f);
    auto res = std::to_chars(char_value, char_value + 4, val);
    if (res.ec == std::errc())
    {
        std::string string_value(char_value);
        string_value.append("%");
        return { string_value };
    }
    else
    {
        return {};
    }
}

void ProgressBar::setValue(float value)
{
    // cap the value between 0.0f and 1.0f
    float cap_val = std::min(1.0f, value);
    float current_val = std::max(0.0f, cap_val);

    // update progress only when the value changes to avoid wasting precious cpu and memory
    if (m_value != current_val)
    {
        // update internal value
        m_value = current_val;
        // recalculate the progress rect
        m_progress_rect = calcProgressRect(current_val);
        // convert value to a percentage in a string format
        m_label->setText(toPercentage(current_val).value_or("%"));
    }
}

float ProgressBar::getValue() const
{
    return m_value;
}

void ProgressBar::setStyle(Style style)
{
    m_style = style;
}

Style& ProgressBar::getStyle()
{
    return m_style;
}