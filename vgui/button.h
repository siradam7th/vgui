#pragma once
#include "common.h"
#include "element.h"
#include "style.h"
#include "label.h"

namespace vgui
{
    class Button : public Element
    {
    public:
        Button(vec4f rect, UPtr<Label> label, Style style);
        void setStyle(Style style);
        Style& getStyle();
        Label& getLabel();
    private:
        UPtr<Label> m_label;
        Style m_style;
    };
}