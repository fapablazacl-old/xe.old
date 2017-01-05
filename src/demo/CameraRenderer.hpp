
#pragma once 

#ifndef __xe_sg_camerarenderer_hpp__
#define __xe_sg_camerarenderer_hpp__

#include "Renderer.hpp"
#include "PhongPipeline.hpp"

namespace xe {
    class CameraRenderer : public Renderer {
    public:
        CameraRenderer(PhongPipeline *pipeline);

        virtual ~CameraRenderer();

        virtual void render(Renderable *renderable);

    private:
        PhongPipeline *m_pipeline;
    };
}

#endif 
