#pragma once
#include "common.h"
#include "element.h"
#include <vector>

namespace vgui
{
    class Canvas
    {
    public:
        Canvas(vec2f size);
        void addElement(SPtr<Element> element);
        void update();
        void draw();
        void resize(vec2f size);
    private:
        vec2f m_size;
        std::vector<SPtr<Element>> m_elements;
    };
}