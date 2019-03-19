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
        void fillRect(vec4f rect, vec4f color) override;
        void fillRectRounded(float radius, vec4f rect, vec4f color) override;
        void strokeRect(vec4f rect, vec4f color) override;
        void strokeRectRounded(float radius, vec4f rect, vec4f color) override;
        bool createFont(const std::string& path, const std::string& name) override;
        void fillFont(const std::string& text, float font_size, const std::string& font_name, vec2f pos, vec4f color, FontStyle font_style) override;
        void destroy() override;
    private:
        NVGcontext* s_nvgContext = nullptr;
    };
}