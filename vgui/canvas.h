#pragma once
#include "common.h"
#include "element.h"
#include <vector>

namespace vgui
{
    class Canvas
    {
    public:
        Canvas(u32 width, u32 height);
        void addElement(SPtr<Element> element);
        void update();
        void draw();
        void resize(u32 width, u32 height);
    private:

        u32 m_width;
        u32 m_height;
        std::vector<SPtr<Element>> m_elements;
    };
}