
#pragma once

#ifndef __xe_sg_phongpipeline_hpp__
#define __xe_sg_phongpipeline_hpp__

#include "Pipeline.hpp"

#include <typeindex>
#include <xe/gfx/Device.hpp>

namespace xe { namespace sg {

    class PhongPipeline : public Pipeline {
    public:
        explicit PhongPipeline(xe::gfx::Device *device);

        virtual ~PhongPipeline();

        virtual xe::Matrix4f getTransformation() const override;

        virtual void setTransformation(const xe::Matrix4f &transformation) override;

        virtual void beginFrame(const xe::Vector4f &clearColor) override;

        virtual void render(Renderable *renderable) override;

        virtual void endFrame() override;

        void registerRenderer(const std::type_index &renderableType, Renderer *renderer);

        void unregisterRenderer(const std::type_index &renderableType, Renderer *renderer);

    private:
        xe::gfx::Device *m_device = nullptr;
        xe::gfx::ProgramPtr m_program;
        xe::Matrix4f m_projViewModel;

        std::map<std::type_index, Renderer*> m_renderers;
    };
}}

#endif
