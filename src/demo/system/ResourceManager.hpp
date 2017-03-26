
#pragma once 

#ifndef __demo_resourcemanager_hpp__
#define __demo_resourcemanager_hpp__

#include <memory>
#include <string>

namespace xe {
    class Archive;
    class Texture;
    class GraphicsDevice;
    class GraphicsManager;
}

namespace demo {
    class ResourceManager {
    public:
        ResourceManager(xe::GraphicsDevice *device, xe::GraphicsManager *manager);

        ~ResourceManager();

        void addArchive(std::unique_ptr<xe::Archive> archive);

        xe::Texture* getTexture(const std::string &name);

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
