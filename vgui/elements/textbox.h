#pragma once
#include "element.h"
#include "vgui/common.h"
#include "vgui/elements/label.h"
#include "vgui/graphics/style.h"
#include "vgui/canvas/canvas_tree_node.h"

namespace vgui
{
    class TextBox : public Element, public CanvasTreeNode
    {
    public:
        TextBox(vec4f rect, UPtr<Label> label, Style style);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void bindUIEvents(UIEvents ui_events) override;
        const UIEvents& getUIEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

    private:
        vec4f m_rect;
        DrawEvents m_draw_events;
        UIEvents m_ui_events;

        UPtr<Label> m_label;
        Style m_style;
    };
}