
#pragma once 

#ifndef __xe_demoresources_hpp__
#define __xe_demoresources_hpp__

#include <memory>

#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/sg/Scene.hpp>

namespace demo {
    /**
     * @brief Holds the manual resource creation, like scenes, materials, etc.
     */
    class DemoResources {
    public:
        DemoResources(xe::GraphicsDevice *device, xe::GraphicsManager *manager);

        ~DemoResources();

        xe::Scene* getScene();

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif 
