#pragma once
#include "vgui/element.h"
#include "vgui/style.h"
#include "vgui/label.h"
#include "vgui/common.h"

namespace vgui
{
    class TextBox : public Element
    {
    public:
        TextBox(vec4f rect, UPtr<Label> label, Style style);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

    private:
        vec4f m_rect;
        DrawEvents m_draw_events;

        UPtr<Label> m_label;
        Style m_style;
    };
}