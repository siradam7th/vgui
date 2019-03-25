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
    private:
        UPtr<Label> m_label;
        Style m_style;
    };
}