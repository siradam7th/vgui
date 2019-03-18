#pragma once
#include "graphics_context.h"
#include "3rdparty/nanovg/nanovg.h"

namespace vgui
{
    class NanovgGraphicsContext : public IGraphicsContext
    {
    public:
        bool init() override;
        void setup() override;
        void beginFrame(vec2f canvas_size);
        void endFrame();
        void drawRoundedRect(float radius, vec4f rect, vec4f color) override;
        void drawRect(vec4f rect, vec4f color) override;
        void destroy() override;
    private:
        NVGcontext* s_nvgContext = nullptr;
    };
}