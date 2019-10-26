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
        Canvas(vec2f size, float pixel_ratio);
        void update();
        void draw();
        void resize(vec2f size, float pixel_ratio);
        CanvasTree* getTree();

    private:
        vec2f m_size;
        float m_pixel_ratio = 1.0f;
        vgui::UPtr<CanvasTree> m_tree;
    };
}