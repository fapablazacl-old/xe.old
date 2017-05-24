
#pragma once

#ifndef __xe_gfx_factorygles2_hpp__
#define __xe_gfx_factorygles2_hpp__

#include <xe/gfx/GraphicsFactory.hpp>

namespace xe { namespace gfx {
    class FactoryGLES2 : public GraphicsFactory {
    public:
        virtual GraphicsDeviceInfo getDeviceInfo() override;

        virtual std::unique_ptr<GraphicsDevice> createDevice() override;
    };
}}

#endif
