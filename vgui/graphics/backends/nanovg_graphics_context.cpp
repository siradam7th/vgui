#include "vgui/graphics/backends/nanovg_graphics_context.h"
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
    // empty for now
}

void NanovgGraphicsContext::beginFrame(vec2f canvas_size)
{
    if (s_nvgContext)
        nvgBeginFrame(s_nvgContext, canvas_size.x, canvas_size.y, 1.0f);
}

void NanovgGraphicsContext::endFrame()
{
    if (s_nvgContext)
        nvgEndFrame(s_nvgContext);
}

void NanovgGraphicsContext::fillRect(vec4f rect, vec4f color)
{
    if (!s_nvgContext)
        return;

    nvgBeginPath(s_nvgContext);
    nvgFillColor(s_nvgContext, nvgRGBAf(color.x, color.y, color.z, color.w));
    nvgRect(s_nvgContext, rect.x, rect.y, rect.z, rect.w);
    nvgFill(s_nvgContext);
}

void NanovgGraphicsContext::fillRectRounded(float radius, vec4f rect, vec4f color)
{
    if (!s_nvgContext)
        return;

    nvgBeginPath(s_nvgContext);
    nvgFillColor(s_nvgContext, nvgRGBAf(color.x, color.y, color.z, color.w));
    nvgRoundedRect(s_nvgContext, rect.x, rect.y, rect.z, rect.w, radius);
    nvgFill(s_nvgContext);
}

void NanovgGraphicsContext::strokeRect(vec4f rect, vec4f color)
{
    if (!s_nvgContext)
        return;

    nvgBeginPath(s_nvgContext);
    nvgStrokeColor(s_nvgContext, nvgRGBAf(color.x, color.y, color.z, color.w));
    nvgRect(s_nvgContext, rect.x, rect.y, rect.z, rect.w);
    nvgStroke(s_nvgContext);
}

void NanovgGraphicsContext::strokeRectRounded(float radius, vec4f rect, vec4f color)
{
    if (!s_nvgContext)
        return;

    nvgBeginPath(s_nvgContext);
    nvgStrokeColor(s_nvgContext, nvgRGBAf(color.x, color.y, color.z, color.w));
    nvgRoundedRect(s_nvgContext, rect.x, rect.y, rect.z, rect.w, radius);
    nvgStroke(s_nvgContext);
}

bool NanovgGraphicsContext::createFont(const std::string& path, const std::string& name)
{
    if (!s_nvgContext)
        return false;

    // note: nanovg keeps track of the loaded fonts and their name internally,so no need to duplicate that
    if (path.empty() || name.empty())
        return false;

    int font_handle = nvgCreateFont(s_nvgContext, name.c_str(), path.c_str());
    if (font_handle != -1)
    {
        return true;
    }

    return false;
}

void NanovgGraphicsContext::fillText(const std::string& text, float font_size, const std::string& font_name, vec2f pos, vec4f color, FontStyle font_style)
{
    if (!s_nvgContext)
        return;

    if (text.empty() || font_name.empty() || font_size < 0.0f)
        return;

    nvgFontFace(s_nvgContext, font_name.c_str());
    nvgFontSize(s_nvgContext, font_size);
    nvgTextAlign(s_nvgContext, NVG_ALIGN_TOP | NVG_ALIGN_LEFT);
    nvgFillColor(s_nvgContext, nvgRGBAf(color.x, color.y, color.z, color.w));
    nvgText(s_nvgContext, pos.x, pos.y, text.c_str(), nullptr);
}

vec4f NanovgGraphicsContext::calcTextBounds(const std::string& text, float font_size, const std::string& font_name)
{
    if (!s_nvgContext)
        return { 0.0f, 0.0f, 0.0f, 0.0f };

    if (text.empty() || font_name.empty() || font_size < 0.0f)
        return { 0.0f, 0.0f, 0.0f, 0.0f };

    float bounds[4];
    nvgFontFace(s_nvgContext, font_name.c_str());
    nvgFontSize(s_nvgContext, font_size);
    nvgTextAlign(s_nvgContext, NVG_ALIGN_TOP | NVG_ALIGN_LEFT);
    nvgTextBounds(s_nvgContext, 0.0f, 0.0f, text.c_str(), nullptr, bounds);
    return { bounds[0], bounds[1], bounds[2], bounds[3] };
}

void NanovgGraphicsContext::destroy()
{
    // empty for now
}