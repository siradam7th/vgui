#include "vgui/label.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Label::Label(vec2f pos, const std::string& text, const std::string& font_name,
    float font_size, Style style, FontStyle font_style) :
    m_text(text), m_font_size(font_size), m_font_name(font_name), m_style(style), m_font_style(font_style)
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    auto bounds = graphics_context->calcTextBounds(text.c_str(), font_size, font_name);
    mi_rect = { pos.x, pos.y, bounds.z, bounds.w };

    auto on_draw = 
        [&rect = mi_rect, &text = m_text, &size = m_font_size,
        &fStyle = m_font_style, &fName= m_font_name, &style = m_style]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        graphics_context->fillText(text, size, fName, { rect.x, rect.y }, style.color, fStyle);
    };
    this->bindDrawEvents({ on_draw });
}