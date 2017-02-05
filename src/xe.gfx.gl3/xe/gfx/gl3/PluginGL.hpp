
#pragma once

#ifndef __xe_gfx_gl3_plugingl_hpp__
#define __xe_gfx_gl3_plugingl_hpp__

#include <xe/Core.hpp>
#include <xe/Plugin.hpp>
#include <xe/gfx/GraphicsFactoryImpl.hpp>

#include "GraphicsDeviceGL.hpp"

namespace xe {
    class PluginGL : public Plugin {
    public:
        PluginGL();
        ~PluginGL();

        virtual PluginData getData() const override;

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

    private:
        xe::FactoryImpl<GraphicsDeviceGL> m_factory;
    };
}

#endif
