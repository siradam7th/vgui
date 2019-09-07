#pragma once
#include "common.h"
#include "element.h"
#include "style.h"
#include "label.h"
#include "canvas_tree_node.h"

namespace vgui
{
    class Button : public Element, public CanvasTreeNode
    {
    public:
        Button(vec4f rect, UPtr<Label> label, Style style);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

        void setStyle(Style style);
        Style& getStyle();
        Label* const getLabel();
    private:
        vec4f m_rect;
        DrawEvents m_draw_events;

        UPtr<Label> m_label;
        Style m_style;
    };
}