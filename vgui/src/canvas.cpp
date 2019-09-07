#include "vgui/canvas.h"
#include "vgui/graphics_device.h"
#include "vgui/canvas_tree_node.h"
using namespace vgui;

Canvas::Canvas(vec2f size) : m_size(size)
{
    m_tree = std::make_unique<CanvasTree>();
}

void Canvas::addElement(SPtr<Element> element)
{
    m_elements.push_back(element);
}

void Canvas::update()
{

}

void Canvas::draw()
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    graphics_context->beginFrame(m_size);
    for (auto& element : m_elements)
    {
        if (auto& on_draw = element->getDrawEvents().on_draw)
        {
            on_draw();
        }
    }

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