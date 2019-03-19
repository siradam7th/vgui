#pragma once
#include "element.h"
#include "font.h"
#include "style.h"
#include <string>

namespace vgui
{
    class Label : public Element
    {
    public:
        Label(vec2f pos, const std::string& text, const std::string& font_name,
            float font_size = default_font_size, Style style = default_style, FontStyle font_style = default_font_style);
    private:
        std::string m_text;
        std::string m_font_name;
        float m_font_size;
        FontStyle m_font_style;
        Style m_style;
    };
}