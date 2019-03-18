#pragma once
#include "common.h"
#include "element.h"
#include "style.h"

namespace vgui
{
    class Button : public Element
    {
    public:
        Button(vec4f rect, Style style);
        void setStyle(Style style);
        Style& getStyle();
    private:
        Style m_style;
    };
}