
#pragma once 

#ifndef __xe_gfx_plugind3d10_hpp__
#define __xe_gfx_plugind3d10_hpp__

#include <string>
#include <Windows.h>
#include <xe/Core.hpp>
#include <xe/Plugin.hpp>

#include "FactoryD3D10.hpp"

namespace xe { namespace gfx {

    class PluginD3D10 : public Plugin<Core> {
    public:
        PluginD3D10();

        virtual ~PluginD3D10();

        virtual PluginData getData() const override;

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

    private:
        HINSTANCE m_hInstance;
        std::string m_class;
        std::unique_ptr<FactoryD3D10> m_factory;
    };
}}

#endif

