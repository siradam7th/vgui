#include "vgui/nanovg_graphics_context.h"
using namespace vgui;

#ifdef VGUI_USE_GL3
#include "3rdparty/glLoadGen/gl_core_3_3.h"
#define NANOVG_GL3_IMPLEMENTATION
#else
#include "3rdparty/glLoadGen/gl_core_2_0.h"
#define NANOVG_GL2_IMPLEMENTATION
#endif
#include "3rdparty/nanovg/nanovg_gl.h"

bool NanovgGraphicsContext::init()
{
#ifdef VGUI_USE_GL3
    s_nvgContext = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG | NVG_ANTIALIAS);
#else
    s_nvgContext = nvgCreateGL2(NVG_STENCIL_STROKES | NVG_DEBUG | NVG_ANTIALIAS);
#endif
    if (s_nvgContext)
    {
        return true;
    }

    return false;
}

void NanovgGraphicsContext::setup()
{

}

void NanovgGraphicsContext::drawRoundedRect(float radius, vec4f rect, vec4f color)
{

}

void NanovgGraphicsContext::drawRect(vec4f rect, vec4f color)
{

}

void NanovgGraphicsContext::destroy()
{

}