
#pragma once

#ifndef __xe_sg_meshrenderer_hpp__
#define __xe_sg_meshrenderer_hpp__

#include "Renderer.hpp"
#include "Mesh.hpp"

#include <xe/gfx/GraphicsDevice.hpp>

namespace xe { 

    class MeshRenderer : public Renderer {
    public:
        explicit MeshRenderer(xe::GraphicsDevice *device);

        virtual ~MeshRenderer();

        virtual void render(Renderable *renderable) override;

    private:
        xe::GraphicsDevice *m_device;
    };
}

#endif 
