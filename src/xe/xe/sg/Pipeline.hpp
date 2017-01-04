
#pragma once

#ifndef __xe_sg_pipeline_hpp__
#define __xe_sg_pipeline_hpp__

#include <memory>

#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/sg/Forward.hpp"

namespace xe {
    class Pipeline {
    public:
        virtual ~Pipeline();
        
        virtual void beginFrame(const xe::Vector4f &color) = 0;
        virtual void endFrame() = 0;

        virtual void render(Light *light) = 0;
        virtual void render(Camera *camera) = 0;
        virtual void render(Geometry *geometry) = 0;
        
        virtual void setWorldTransform(const Matrix4f &) = 0;
    };

    typedef std::unique_ptr<Pipeline> PipelinePtr;
}

#endif 
