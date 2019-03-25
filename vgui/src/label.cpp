#include "vgui/label.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Label::Label(const std::string& text, const std::string& font_name, vec2f pos,
    float font_size, Style style, FontStyle font_style) :
    m_text(text), m_font_size(font_size), m_font_name(font_name), m_style(style), m_font_style(font_style)
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    auto bounds = graphics_context->calcTextBounds(text.c_str(), font_size, font_name);
    mi_rect = { pos.x, pos.y, bounds.z, bounds.w };

    auto on_draw = [this]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        graphics_context->fillText(m_text, m_font_size, m_font_name, { mi_rect.x, mi_rect.y }, m_style.color, m_font_style);
    };
    this->bindDrawEvents({ on_draw });
}

void Label::setText(const std::string& text)
{
    m_text = text;
}

void Label::setFontSize(float size)
{
    m_font_size = size;
}

void Label::setFontStyle(FontStyle font_style)
{
    m_font_style = font_style;
}

void Label::setStyle(Style style)
{
    m_style = style;
}

const std::string& Label::getText() const
{
    return m_text;
}

float Label::getFontSize() const
{
    return m_font_size;
}

const FontStyle& Label::getFontStyle() const
{
    return m_font_style;
}

const Style& Label::getStyle() const
{
    return m_style;
}