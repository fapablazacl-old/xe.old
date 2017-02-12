
#pragma once

#ifndef __xe_sg_pipeline_hpp__
#define __xe_sg_pipeline_hpp__

#include <xe/Matrix.hpp>
#include <xe/Vector.hpp>

namespace xe { 
    class Renderable;
    class Renderer;

    enum class TransformType {
        Model,
        View, 
        Proj
    };
    
    /**
     * @brief Graphics pipeline abstracion. Used by the Scene Renderer.
     */
    class Pipeline {
    public:
        virtual ~Pipeline();

        virtual xe::Matrix4f getProjViewModel() const = 0;

        virtual xe::Matrix4f getTransform(const TransformType transformType) const = 0;

        virtual void setTransform(const TransformType transformType, const xe::Matrix4f &transformation) = 0;

        virtual void beginFrame() = 0;

        virtual void render(Renderable *renderable) = 0;

        virtual void endFrame() = 0;
    };
}

#endif
