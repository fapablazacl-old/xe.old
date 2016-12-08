
#pragma once

#ifndef __xe_sg_meshrenderer_hpp__
#define __xe_sg_meshrenderer_hpp__

#include "Renderer.hpp"
#include "Mesh.hpp"

#include <xe/gfx/Device.hpp>

namespace xe { namespace sg {  

    class MeshRenderer : public Renderer {
    public:
        explicit MeshRenderer(xe::gfx::Device *device);

        virtual ~MeshRenderer();

        virtual void render(Renderable *renderable) override;

    private:
        xe::gfx::Device *m_device;
    };
}}

#endif 
