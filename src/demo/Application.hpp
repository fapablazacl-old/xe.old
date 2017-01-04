
#pragma once 

#ifndef __demo_application_hpp__
#define __demo_application_hpp__

#include <xe/Core.hpp>

#include <iostream>
#include <map>
#include <xe/Core.hpp>
#include <xe/Matrix.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Scene.hpp>

#include "Renderable.hpp"
#include "SceneRenderer.hpp"
#include "Pipeline.hpp"

namespace demo {
    class Application : public xe::Core {
    public:
        Application();

        ~Application();

        int run();
        
    private:
        xe::GraphicsDevicePtr createDevice();

        xe::MeshFormatPtr createMeshFormat();

        xe::ScenePtr createScene();
        
        xe::MaterialPtr createCustomMaterial();
        
        xe::MaterialPtr createBlankMaterial();
        
        std::map<std::string, xe::MaterialPtr> createMaterials();

        std::map<std::string, xe::RenderablePtr> createRenderables();
        
        xe::TexturePtr createTexture(const std::string &file);
        
        std::map<std::string, xe::TexturePtr> createTextures();
        
        xe::RenderablePtr createSphereRenderable();

        xe::RenderablePtr createPlaneRenderable();

        xe::RenderablePtr createLightRenderable();

    private:
        xe::GraphicsDevicePtr m_device;
        xe::MeshFormatPtr m_meshFormat;
        xe::ScenePtr m_scene;

        xe::SceneNode *m_meshNode = nullptr;
        //float m_angle = 0.0f;

        std::map<std::string, xe::RenderablePtr> m_renderables;
        std::map<std::string, xe::MaterialPtr> m_materials;
        std::map<std::string, xe::TexturePtr> m_textures;

        std::unique_ptr<xe::Pipeline> m_pipeline;
        std::unique_ptr<xe::SceneRenderer> m_sceneRenderer;
    };
}

#endif
