#pragma once
#include "common.h"
#include "element.h"
#include "style.h"

namespace vgui
{
    class Button : public Element
    {
    public:
        Button(vec4f rect);
        void setStyle(Style style);
    private:
        Style m_style;
    };
}