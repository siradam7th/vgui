#include "vgui/label.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Label::Label(const std::string& text, const std::string& font_name, vec2f pos,
    float font_size, Style style, FontStyle font_style) :
    m_text(text), m_font_size(font_size), m_font_name(font_name), m_style(style), m_font_style(font_style)
{
    mi_rect = calcTextBounds(pos, text, font_name, font_size);

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        graphics_context->fillText(m_text, m_font_size, m_font_name, { mi_rect.x, mi_rect.y }, m_style.color, m_font_style);
    };
    this->bindDrawEvents({ on_draw });
}

vec4f Label::calcTextBounds(const vec2f& pos, const std::string& text, const std::string& font_name, float font_size)
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    auto bounds = graphics_context->calcTextBounds(text.c_str(), font_size, font_name);

    return vec4f
    {
        pos.x, pos.y, bounds.z, bounds.w
    };
}

void Label::setText(const std::string& text)
{
    m_text = text;
    // recalculate text bounds
    mi_rect = calcTextBounds({ mi_rect.x, mi_rect.y }, text, m_font_name, m_font_size);
}

void Label::setFontName(const std::string& font_name)
{
    m_font_name = font_name;
    // recalculate text bounds
    mi_rect = calcTextBounds({ mi_rect.x, mi_rect.y }, m_text, m_font_name, m_font_size);
}

void Label::setFontSize(float size)
{
    m_font_size = size;
    // recalculate text bounds
    mi_rect = calcTextBounds({ mi_rect.x, mi_rect.y }, m_text, m_font_name, m_font_size);
}

void Label::setFontStyle(FontStyle font_style)
{
    m_font_style = font_style;
    // TODO: uncomment calcTextBounds() line once FontStyle is supported here in Label
    // recalculate text bounds
    //mi_rect = calcTextBounds({ mi_rect.x, mi_rect.y }, m_text, m_font_name, m_font_size);
}

void Label::setStyle(Style style)
{
    m_style = style;
}

const std::string& Label::getText() const
{
    return m_text;
}

const std::string& Label::getFontName() const
{
    return m_font_name;
}

float Label::getFontSize() const
{
    return m_font_size;
}

const FontStyle& Label::getFontStyle() const
{
    return m_font_style;
}

Style& Label::getStyle()
{
    return m_style;
}