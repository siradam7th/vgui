#include "vgui/button.h"
using namespace vgui;

Button::Button(u32 width, u32 height) : m_width(width), m_height(height)
{

}


void Button::setStyle(Style style)
{
    m_style = style;
}