#pragma once
#include "common.h"
#include "element.h"
#include <vector>
#include "canvas_tree.h"

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