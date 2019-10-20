#pragma once
#include "graphics_device.h"
#include "backends/nanovg_graphics_context.h"
using namespace vgui;

IGraphicsContext* GraphicsDevice::createGraphicsContext(GraphicsDeviceType device_type)
{
    switch (device_type)
    {
    case vgui::GraphicsDeviceType::Nanovg:
        s_graphicsContext = new NanovgGraphicsContext();
        break;
    default:
        s_graphicsContext = nullptr;
        break;
    }

    return s_graphicsContext;
}

void GraphicsDevice::destroyGraphicsContext()
{
    if (s_graphicsContext)
    {
        // call the destruction function first to release resources
        // that are used by the graphics context to avoid leaking memory
        s_graphicsContext->destroy();
        delete s_graphicsContext;
    }
}

IGraphicsContext* GraphicsDevice::getGraphicsContext()
{
    return s_graphicsContext;
}
