#pragma once
#include "graphics_device.h"
#include "backends/nanovg_graphics_context.h"
using namespace vgui;

IGraphicsContext* GraphicsDevice::s_graphicsContext = nullptr;

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

IGraphicsContext* GraphicsDevice::getGraphicsContext()
{
    return s_graphicsContext;
}