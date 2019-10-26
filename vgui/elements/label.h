#pragma once
#include "element.h"
#include "vgui/graphics/font.h"
#include "vgui/graphics/style.h"
#include "vgui/canvas/canvas_tree.h"

#include <string>

namespace vgui
{
    class Label : public Element, public CanvasTreeNode
    {
    public:
        Label() = default;

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void bindUIEvents(UIEvents ui_events) override;
        const UIEvents& getUIEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

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
        vec4f m_rect;
        DrawEvents m_draw_events;
        UIEvents m_ui_events;

        // calculate text bounds
        vec4f calcTextBounds(const vec2f& pos, const std::string& text, const std::string& font_name, float font_size);

        std::string m_text;
        std::string m_font_name;
        FontStyle m_font_style;
        float m_font_size;
        Style m_style;
    };
}