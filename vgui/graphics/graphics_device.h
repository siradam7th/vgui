#pragma once
#include "graphics_context.h"

namespace vgui
{
    enum class GraphicsDeviceType
    {
        Nanovg,
    };

    class GraphicsDevice
    {
    public:
        static IGraphicsContext* createGraphicsContext(GraphicsDeviceType device_type);
        static void destroyGraphicsContext();
        static IGraphicsContext* getGraphicsContext();
    private:
        inline static IGraphicsContext* s_graphicsContext = nullptr;
    };
}