#pragma once
#include "element.h"
#include "vgui/common.h"
#include "vgui/graphics/style.h"
#include "vgui/canvas/canvas_tree.h"

namespace vgui
{
    class CheckBox : public Element, public CanvasTreeNode
    {
    public:
        CheckBox(vec4f rect, bool checked, Style style);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

        bool isChecked();
        bool toggle();

        void setStyle(Style style);
        Style& getStyle();
    private:
        vec4f m_rect;
        DrawEvents m_draw_events;

        bool m_checked;
        Style m_style;
    };
}