#pragma once
#include "3rdparty/nanovg/nanovg.h"
#include "vgui/graphics/graphics_context.h"

namespace vgui
{
    class NanovgGraphicsContext : public IGraphicsContext
    {
    public:
        bool init() override;
        void setup() override;
        void beginFrame(vec2f canvas_size, float pixel_ratio);
        void endFrame();
        void fillRect(vec4f rect, vec4f color) override;
        void fillRectRounded(float radius, vec4f rect, vec4f color) override;
        void strokeRect(vec4f rect, vec4f color) override;
        void strokeRectRounded(float radius, vec4f rect, vec4f color) override;
        bool createFont(const std::string& path, const std::string& name) override;
        void fillText(const std::string& text, float font_size, const std::string& font_name, vec2f pos, vec4f color, FontStyle font_style) override;
        vec4f calcTextBounds(const std::string& text, float font_size, const std::string& font_name) override;
        void destroy() override;
    private:
        NVGcontext* s_nvgContext = nullptr;
    };
}