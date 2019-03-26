#pragma once
#include "common.h"
#include "element.h"
#include "style.h"

namespace vgui
{
    class CheckBox : public Element
    {
    public:
        CheckBox(vec4f rect, bool checked, Style style);
        bool isChecked();
        bool toggle();

        void setStyle(Style style);
        Style& getStyle();
    private:
        bool m_checked;
        Style m_style;
    };
}