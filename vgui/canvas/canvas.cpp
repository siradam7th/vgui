#include "canvas.h"
#include "canvas_tree_node.h"
#include "vgui/graphics/graphics_device.h"
using namespace vgui;

Canvas::Canvas(vec2f size, float pixel_ratio) : m_size(size), m_pixel_ratio(pixel_ratio)
{
    m_tree = std::make_unique<CanvasTree>();
}

void Canvas::update(vec2f mouse_position)
{
    auto root = m_tree->getRoot();
    if (root)
    {
        root->traverse([&](CanvasTreeNode * node) -> bool
            {
                // Note: no need to check if node is nullptr, because traverse doesn't call us when node is nullptr
                auto const el = node->getElement();
                if (el == nullptr)
                {
                    return false;
                }

                auto const rect = el->getRect();
                if (vgui::intersect_rect_mouse(
                    mouse_position.x, mouse_position.y,
                    rect.x, rect.y, rect.z, rect.w))
                {
                    const auto ui_events = el->getUIEvents();
                    if (const auto& on_mouse_hover = ui_events.on_mouse_hover)
                    {
                        on_mouse_hover();
                    }
                }
                return false;
            }
        );
    }
}

void Canvas::draw()
{
    auto graphics_context = GraphicsDevice::getGraphicsContext();
    graphics_context->beginFrame(m_size, m_pixel_ratio);

    auto root = m_tree->getRoot();
    if (root)
    {
        root->traverse([&](CanvasTreeNode* node) -> bool
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
                    on_draw(graphics_context);
                }
                return false;
            }
        );
    }

    graphics_context->endFrame();
}

void Canvas::resize(vec2f size, float pixel_ratio)
{
    m_size = size;
    m_pixel_ratio = pixel_ratio;
}

CanvasTree* Canvas::getTree()
{
    return m_tree.get();
}