
#pragma once

#ifndef __xe_gfx_plugingles2_hpp__
#define __xe_gfx_plugingles2_hpp__

#include <xe/Core.hpp>
#include <xe/Plugin.hpp>

#include "FactoryGLES2.hpp"

namespace xe { namespace gfx {
    class PluginGLES2 : public Plugin<Core> {
    public:
        PluginGLES2();

        virtual ~PluginGLES2();

        virtual PluginData getData() const override;

        virtual void start(Core *core) override;

        virtual void stop(Core *core) override;

    private:
        FactoryGLES2 m_factory;
    };
}}

#endif
