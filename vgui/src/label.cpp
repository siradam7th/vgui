#include "vgui/label.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Label::Label(vec2f pos, const std::string& text, const std::string& font_name,
    float font_size, Style style, FontStyle font_style) :
    m_text(text), m_font_size(font_size), m_font_name(font_name), m_style(style), m_font_style(font_style)
{
    // TODO: figure out the width and height of the text
    mi_rect = { pos.x, pos.y, 0.0f, 0.0f };

    auto on_draw = 
        [&rect = mi_rect, &text = m_text, &size = m_font_size,
        &fStyle = m_font_style, &fName= m_font_name, &style = m_style]()
    {
        auto graphics_context = GraphicsDevice::getGraphicsContext();
        graphics_context->fillFont(text, size, fName, { rect.x, rect.y }, style.color, fStyle);
    };
    this->bindDrawEvents({ on_draw });
}