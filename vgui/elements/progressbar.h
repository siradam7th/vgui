#pragma once
#include "element.h"
#include "label.h"
#include "vgui/graphics/style.h"
#include "vgui/canvas/canvas_tree_node.h"

#include <optional>
#include <string>

namespace vgui
{
    class ProgressBar : public Element, public CanvasTreeNode
    {
    public:
        // Label is drawn correctly only when font_name is a valid loaded font
        // 'value' is in range [0-1] else it's capped inside that range to keep everything functioning correctly
        ProgressBar(vec4f rect, float value, Style style, const std::string& font_name = "", vec4f label_color = default_style.color);

        // Implement Element interface
        void bindDrawEvents(DrawEvents draw_events) override;
        const DrawEvents& getDrawEvents() override;
        void setRect(vec4f rect) override;
        const vec4f& getRect() override;

        void setValue(float value);
        float getValue() const;

        void setStyle(Style style);
        Style& getStyle();
    private:
        vec4f m_rect;
        DrawEvents m_draw_events;

        // convert float range [0-1] to 4 characters string (3 digits + '%') in range [0-100]
        std::optional<std::string> toPercentage(float value);
        // calculate progress rect according to 'value'
        inline vec4f calcProgressRect(float value);

        float m_value = 0.0f;
        UPtr<Label> m_label;
        vec4f m_progress_rect;
        Style m_style;
    };
}