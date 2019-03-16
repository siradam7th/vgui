#pragma once
#include "common.h"
#include "element.h"
#include "style.h"

namespace vgui
{
    class Button : public Element
    {
    public:
        Button(u32 width, u32 height);
        void setStyle(Style style);
    private:

        u32 m_width;
        u32 m_height;
        Style m_style;
    };
}