
#pragma once 

#ifndef __demo_application_hpp__
#define __demo_application_hpp__

#include <xe/Core.hpp>

#include <iostream>
#include <map>
#include <xe/Core.hpp>
#include <xe/Matrix.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/gfx/Device.hpp>
#include <xe/gfx/DeviceInfo.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/Renderable.hpp>

namespace demo {
    class Application : public xe::Core {
    public:
        Application();

        ~Application();

        int run();

    private:
        xe::gfx::DevicePtr createDevice();

        xe::gfx::ProgramPtr createProgram();

        xe::gfx::MeshFormatPtr createMeshFormat();

        xe::sg::ScenePtr createScene();
        
        std::map<std::string, xe::sg::RenderablePtr> createRenderableMap();

    private:
        xe::gfx::DevicePtr m_device;
        xe::gfx::ProgramPtr m_program;
        xe::gfx::MeshFormatPtr m_meshFormat;
        xe::sg::ScenePtr m_scene;

        std::map<std::string, xe::sg::RenderablePtr> m_renderableMap;
    };
}

#endif
