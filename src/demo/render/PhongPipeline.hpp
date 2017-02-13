
#pragma once

#ifndef __xe_sg_phongpipeline_hpp__
#define __xe_sg_phongpipeline_hpp__

#include "Pipeline.hpp"

#include <typeindex>
#include <array>
#include <xe/gfx/GraphicsDevice.hpp>

namespace xe {

    class PhongPipeline : public Pipeline {
    public:
        explicit PhongPipeline(GraphicsDevice *device);

        virtual ~PhongPipeline();

        virtual xe::Matrix4f getProjViewModel() const override;

        virtual xe::Matrix4f getTransform(const TransformType transformType) const override;

        virtual void setTransform(const TransformType transformType, const xe::Matrix4f &transform) override;

        virtual void beginFrame() override;

        virtual void render(Renderable *renderable) override;

        virtual void endFrame() override;

    protected:
        void syncModelViewProj();

        void registerRenderer(const std::type_index &renderableType, Renderer *renderer);

        void unregisterRenderer(const std::type_index &renderableType, Renderer *renderer);

    private:
        xe::GraphicsDevice *m_device = nullptr;
        xe::ProgramPtr m_program;

        std::array<xe::Matrix4f, 3> m_transforms;

        xe::Matrix4f m_mvpTransform = xe::Matrix4f::makeIdentity();

        std::vector<std::unique_ptr<Renderer>> m_renderersStorage;

        std::map<std::type_index, Renderer*> m_renderers;

        bool m_frame = false;
    };
}

#endif
