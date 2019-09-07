#pragma once
#include "canvas_tree.h"
#include "vgui/common.h"
#include "vgui/elements/element.h"

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
        CanvasTree* getTree();

    private:
        vec2f m_size;
        std::vector<SPtr<Element>> m_elements;
        vgui::UPtr<CanvasTree> m_tree;
    };
}