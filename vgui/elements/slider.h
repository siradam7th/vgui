#pragma once
#include "element.h"
#include "vgui/common.h"
#include "vgui/graphics/style.h"
#include "vgui/canvas/canvas_tree_node.h"

namespace vgui
{
    class Slider : public Element, public CanvasTreeNode
    {
    public:
        Slider(vec4f rect, float value, Style style);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void bindUIEvents(UIEvents ui_events) override;
        const UIEvents& getUIEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

        // setters
        void setValue(float value);
        void setStyle(Style style);

        // getters
        float getValue() const;
        Style& getStyle();
    private:
        vec4f m_rect;
        vec4f m_borders_rect;
        DrawEvents m_draw_events;
        UIEvents m_ui_events;

        // calculate the rect of the knob based on the current slider rect
        inline vec4f calcKnobRect(float value, vec2f knob_rect_size);

        float m_value;
        vec4f m_knob_rect;
        Style m_style;
    };
}