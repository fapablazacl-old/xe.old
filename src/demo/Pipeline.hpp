
#pragma once

#ifndef __xe_sg_pipeline_hpp__
#define __xe_sg_pipeline_hpp__

#include <xe/Matrix.hpp>
#include <xe/Vector.hpp>

namespace xe { namespace sg {
    class Renderable;
    class Renderer;

    class Pipeline {
    public:
        virtual ~Pipeline();

        virtual xe::Matrix4f getTransformation() const = 0;

        virtual void setModelMatrix(const xe::Matrix4f &transformation) = 0;

        virtual void beginFrame(const xe::Vector4f &clearColor) = 0;

        virtual void render(Renderable *renderable) = 0;

        virtual void endFrame() = 0;
    };
}}

#endif
