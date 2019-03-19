#pragma once
#include "math.h"
#include "font.h"
#include <string>

namespace vgui
{
    class IGraphicsContext
    {
    public:
        virtual bool init() = 0; // initialize (nanovg, skia, own implementation...)
        virtual void setup() = 0; // load default resources such as fonts
        virtual void beginFrame(vec2f canvas_size) = 0; // called by the canvas at the start of a drawing frame
        virtual void endFrame() = 0; // called by the canvas at the end of a drawing frame
        virtual void fillRect(vec4f rect, vec4f color) = 0;
        virtual void fillRectRounded(float radius, vec4f rect, vec4f color) = 0;
        virtual void strokeRect(vec4f rect, vec4f color) = 0;
        virtual void strokeRectRounded(float radius, vec4f rect, vec4f color) = 0;
        virtual bool createFont(const std::string& path, const std::string& name) = 0;
        virtual void fillFont(const std::string& text, float font_size, const std::string& font_name, vec2f pos, vec4f color, FontStyle font_style) = 0;
        virtual void destroy() = 0; // deallocate resources that were allocated in setup() and destroy objects such as context
    };
}