
#pragma once

#ifndef __xe_gfx_gl3_plugingl_hpp__
#define __xe_gfx_gl3_plugingl_hpp__

#include <xe/sys/Plugin.hpp>
#include <xe/gfx/FactoryImpl.hpp>

#include "DeviceGL.hpp"

namespace xe { namespace gfx { namespace gl3 {
    class PluginGL : public xe::sys::Plugin {
    public:
        PluginGL();
        ~PluginGL();

        virtual std::string getName() const override;

        virtual std::string getDescription() const override;
           
        virtual Version getVersion() const override;

        virtual void initialize(Core *core) override;
           
        virtual void terminate() override;

    private:
        xe::Core *m_core = nullptr;
        xe::gfx::FactoryImpl<DeviceGL> m_factory;
    };
}}}

#endif
