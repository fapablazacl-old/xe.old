
#include "ResourceManager.hpp"

#include <vector>
#include <map>
#include <xe/io/Archive.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/gfx/GraphicsManager.hpp>

namespace demo {
    struct ResourceManager::Private {
        std::vector<std::unique_ptr<xe::Archive>> m_archives;

        std::map<std::string, std::unique_ptr<xe::Texture>> m_textures;

        xe::GraphicsDevice *m_device = nullptr;
        xe::GraphicsManager *m_manager = nullptr;

        std::unique_ptr<xe::Stream> getStream(const std::string &name) {
            std::unique_ptr<xe::Stream> stream;

            for (auto &archive : m_archives) {
                if (stream = archive->open(name)) {
                    break;
                }
            }

            return stream;
        }
    };

    ResourceManager::ResourceManager(xe::GraphicsDevice *device, xe::GraphicsManager *manager) 
        : m_impl(new ResourceManager::Private()) {
    
        m_impl->m_device = device;
        m_impl->m_manager = manager;
    }

    ResourceManager::~ResourceManager() {}

    void ResourceManager::addArchive(std::unique_ptr<xe::Archive> archive) {
        m_impl->m_archives.push_back(std::move(archive));
    }

    xe::Texture* ResourceManager::getTexture(const std::string &name) {
        // INFO: consider for now a image as a texture, defaulting to RGB_8 format.

        if (m_impl->m_textures[name].get()) {
            return m_impl->m_textures[name].get();
        }

        std::unique_ptr<xe::Stream> stream = m_impl->getStream(name);

        if (!stream) {
            return nullptr;
        }

        std::clog << "demo::ResourceManager::getTexture: Loading texture '" << name << "'" << std::endl;

        std::unique_ptr<xe::Image> image = m_impl->m_manager->createImage(stream.get());
        assert(image);
        
        const xe::ImageDesc imageDesc = image->getDesc();
        
        assert(imageDesc.format != xe::PixelFormat::Unknown);
        
        xe::TextureDesc desc;
        desc.type = xe::TextureType::Tex2D;
        desc.format = xe::PixelFormat::RGB_8;
        desc.width = imageDesc.width;
        desc.height = imageDesc.height;

        std::unique_ptr<xe::Texture> texture = m_impl->m_device->createTexture (
            desc, 
            imageDesc.format, 
            xe::getDataType(imageDesc.format), 
            image->getPointer()
        );

        m_impl->m_textures[name] = std::move(texture);

        return m_impl->m_textures[name].get();
    }
}
