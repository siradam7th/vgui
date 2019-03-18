#include "vgui/canvas.h"
#include "vgui/graphics_device.h"
using namespace vgui;

Canvas::Canvas(vec2f size) : m_size(size)
{

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
    graphics_context->endFrame();
}

void Canvas::resize(vec2f size)
{
    m_size = size;
}
