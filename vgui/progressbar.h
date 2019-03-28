#pragma once
#include "element.h"
#include "style.h"
#include "label.h"
#include <optional>

namespace vgui
{
    class ProgressBar : public Element
    {
    public:
        // Label is drawn correctly only when font_name is a valid loaded font
        // 'value' is in range [0-1] else it's capped inside that range to keep everything functioning correctly
        ProgressBar(vec4f rect, float value, Style style, const std::string& font_name = "", vec4f label_color = default_style.color);
        void setValue(float value);
        float getValue() const;

        void setStyle(Style style);
        Style& getStyle();
    private:
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