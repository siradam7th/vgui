#include "label.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

Label::Label(const std::string& text, const std::string& font_name, vec2f pos,
    float font_size, Style style, FontStyle font_style) :
    m_text(text), m_font_size(font_size), m_font_name(font_name),
    m_style(style), m_font_style(font_style)
{
    // setting the element is required for CanvasTree to function correctly
    setElement(this);

    // since we don't know how much space the text takes yet, we set it to zero
    m_rect = vec4f{ pos.x, pos.y, 0.0f, 0.0f };
    auto on_draw = [this](IGraphicsContext* graphics_context)
    {
        graphics_context->fillText(m_text, m_font_size, m_font_name, { m_rect.x, m_rect.y }, m_style.color, m_font_style);
    };

    auto on_update = [this]()
    {
        // calculate the rect of the text
        m_rect = calcTextBounds({ m_rect.x, m_rect.y }, m_text, m_font_name, m_font_size);
    };

    // issue the first update, this is important and mainly to avoid duplicating code
    on_update();
    this->bindDrawEvents({ on_draw, on_update });
}

void Label::bindDrawEvents(DrawEvents draw_events)
{
    m_draw_events = draw_events;
}

const DrawEvents& Label::getDrawEvents()
{
    return m_draw_events;
}

void Label::setRect(vec4f rect)
{
    m_rect = rect;
}

const vec4f& Label::getRect()
{
    return m_rect;
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
    m_rect = calcTextBounds({ m_rect.x, m_rect.y }, text, m_font_name, m_font_size);
}

void Label::setFontName(const std::string& font_name)
{
    m_font_name = font_name;
    // recalculate text bounds
    m_rect = calcTextBounds({ m_rect.x, m_rect.y }, m_text, m_font_name, m_font_size);
}

void Label::setFontSize(float size)
{
    m_font_size = size;
    // recalculate text bounds
    m_rect = calcTextBounds({ m_rect.x, m_rect.y }, m_text, m_font_name, m_font_size);
}

void Label::setFontStyle(FontStyle font_style)
{
    m_font_style = font_style;
    // TODO: uncomment calcTextBounds() line once FontStyle is supported here in Label
    // recalculate text bounds
    //m_rect = calcTextBounds({ m_rect.x, m_rect.y }, m_text, m_font_name, m_font_size);
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