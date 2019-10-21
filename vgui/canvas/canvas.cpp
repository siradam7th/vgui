#include "canvas.h"
#include "canvas_tree_node.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

Canvas::Canvas(vec2f size) : m_size(size)
{
    m_tree = std::make_unique<CanvasTree>();
}

void Canvas::update()
{

}

void Canvas::draw()
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    graphics_context->beginFrame(m_size);

    auto root = m_tree->getRoot();
    if (root)
    {
        root->traverse([](CanvasTreeNode* node) -> bool
            {
                // Note: no need to check if node is nullptr, because traverse doesn't call us when node is nullptr
                auto const el = node->getElement();
                if (el == nullptr)
                {
                    return false;
                }

                auto draw_events = el->getDrawEvents();
                if (auto& on_draw = draw_events.on_draw)
                {
                    on_draw();
                }
                return false;
            }
        );
    }

    graphics_context->endFrame();
}

void Canvas::resize(vec2f size)
{
    m_size = size;
}

CanvasTree* Canvas::getTree()
{
    return m_tree.get();
}