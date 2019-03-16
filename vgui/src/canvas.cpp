#include "vgui/canvas.h"
using namespace vgui;

Canvas::Canvas(u32 width, u32 height) : m_width(width), m_height(height)
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

}

void Canvas::resize(u32 width, u32 height)
{
    m_width = width;
    m_height = height;
}
