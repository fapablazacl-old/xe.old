
#pragma once

#ifndef __xe_sg_phongpipeline_hpp__
#define __xe_sg_phongpipeline_hpp__

#include <array>
#include <xe/math/Matrix.hpp>
#include <xe/gfx/GraphicsDevice.hpp>

namespace xe {
    enum class TransformType {
        Model,
        View, 
        Proj
    };

    class PhongPipeline {
    public:
        explicit PhongPipeline(GraphicsDevice *device);

        ~PhongPipeline();

        xe::Matrix4f getTransform(const TransformType transformType) const;

        void setTransform(const TransformType transformType, const xe::Matrix4f &transform);

        void beginFrame();

        void endFrame();

        GraphicsDevice *getDevice() {
            return m_device;
        }

    protected:
        void syncModelViewProj();

    private:
        xe::GraphicsDevice *m_device = nullptr;
        xe::ProgramPtr m_program;
        std::array<xe::Matrix4f, 3> m_transforms;
        xe::Matrix4f m_mvpTransform = xe::Matrix4f::makeIdentity();
        bool m_frame = false;
    };
}

#endif
