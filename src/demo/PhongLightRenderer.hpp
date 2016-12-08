
#pragma once 

#ifndef __xe_sg_phonglightrenderer_hpp__
#define __xe_sg_phonglightrenderer_hpp__

#include "Renderer.hpp"

#include <xe/gfx/Device.hpp>

namespace xe { namespace sg {

    class PhongLightRenderer : public Renderer {
    public:
        PhongLightRenderer(xe::gfx::Device *device);
        virtual ~PhongLightRenderer();

        virtual void render(Renderable *renderable);

    private:
        xe::gfx::Device *m_device;
    };
}}

#endif 
