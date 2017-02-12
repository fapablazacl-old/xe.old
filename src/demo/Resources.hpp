
#pragma once 

#ifndef __xe_resources_hpp__
#define __xe_resources_hpp__

#include <memory>

#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/sg/Scene.hpp>

namespace demo {
    /**
     * @brief Holds the manual resource creation, loading and generation, like scenes, materials, textures, etc.
     */
    class Resources {
    public:
        Resources(xe::GraphicsDevice *device, xe::GraphicsManager *manager);

        ~Resources();

        xe::Scene* getScene();

        xe::Renderable* getRenderable(const std::string &name);

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif 
