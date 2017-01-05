
#pragma once 

#ifndef __xe_sg_phonglightrenderer_hpp__
#define __xe_sg_phonglightrenderer_hpp__

#include "Renderer.hpp"

#include <xe/gfx/GraphicsDevice.hpp>

namespace xe {

    class PhongLightRenderer : public Renderer {
    public:
        PhongLightRenderer(xe::GraphicsDevice *device);
        virtual ~PhongLightRenderer();

        virtual void render(Renderable *renderable);

    private:
        xe::GraphicsDevice *m_device;
    };
}

#endif 
