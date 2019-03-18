#pragma once
#include "math.h"

namespace vgui
{
    class IGraphicsContext
    {
    public:
        virtual bool init() = 0; // initialize (nanovg, skia, own implementation...)
        virtual void setup() = 0; // load default resources such as fonts
        virtual void beginFrame(vec2f canvas_size) = 0; // called by the canvas at the start of a drawing frame
        virtual void endFrame() = 0; // called by the canvas at the end of a drawing frame
        virtual void drawRoundedRect(float radius, vec4f rect, vec4f color) = 0;
        virtual void drawRect(vec4f rect, vec4f color) = 0;
        virtual void destroy() = 0; // deallocate resources that were allocated in setup() and destroy objects such as context
    };
}