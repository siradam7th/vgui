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
        Label() = default;
        Label(const std::string& text, const std::string& font_name, vec2f pos = {0.0f, 0.0f},
            float font_size = default_font_size, Style style = default_style, FontStyle font_style = default_font_style);
        // setters
        void setText(const std::string& text);
        void setFontName(const std::string& font_name);
        void setFontSize(float size);
        void setFontStyle(FontStyle font_style);
        void setStyle(Style style);

        // getters
        const std::string& getText() const;
        const std::string& getFontName() const;
        float getFontSize() const;
        const FontStyle& getFontStyle() const;
        Style& getStyle();
    private:
        // calculate text bounds
        vec4f calcTextBounds(const vec2f& pos, const std::string& text, const std::string& font_name, float font_size);

        std::string m_text;
        std::string m_font_name;
        FontStyle m_font_style;
        float m_font_size;
        Style m_style;
    };
}