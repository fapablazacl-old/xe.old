
#pragma once 

#ifndef __demo_application_hpp__
#define __demo_application_hpp__

#include <xe/Core.hpp>
#include <xe/gfx/GraphicsDevice.hpp>

#include "DemoResources.hpp"
#include "ResourceManager.hpp"
#include "render/Renderable.hpp"
#include "render/SceneRenderer.hpp"
#include "render/Pipeline.hpp"

namespace demo {
    class Application : public xe::Core {
    public:
        Application();

        ~Application();

        int run();
        
    private:
        std::unique_ptr<xe::GraphicsDevice> createDevice();

    private:
        std::unique_ptr<xe::GraphicsDevice> m_device;

        xe::SceneNode *m_meshNode = nullptr;
        //float m_angle = 0.0f;

        std::unique_ptr<xe::Pipeline> m_pipeline;
        std::unique_ptr<xe::SceneRenderer> m_sceneRenderer;

        std::unique_ptr<DemoResources> m_resources;
    };
}

#endif
