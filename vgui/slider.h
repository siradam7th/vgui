#pragma once
#include "common.h"
#include "element.h"
#include "style.h"

namespace vgui
{
    class Slider : public Element
    {
    public:
        Slider(vec4f rect, float value, Style style);

        // setters
        void setValue(float value);
        void setStyle(Style style);

        // getters
        float getValue() const;
        Style& getStyle();
    private:
        // calculate the rect of the knob based on the current slider rect
        inline vec4f calcKnobRect(float value, vec2f knob_rect_size);

        float m_value;
        vec4f m_knob_rect;
        Style m_style;
    };
}