
#include <xe/Core.hpp>
#include <xe/Plugin.hpp>
#include <cassert>

#include "ImageLoaderPNG.hpp"

namespace xe {
    class PluginPNG : public xe::Plugin {
    public:
        virtual PluginData getData() const override {
            return {"lodepng based Image Loader", "", {1, 0}};
        }

        virtual void start(Core *core) override {
            assert(core);
            assert(!m_imageLoader);

            m_imageLoader = std::make_unique<ImageLoaderPNG>();
            
            core->getGraphicsManager()->registerImageLoader(m_imageLoader.get());
        }

        virtual void stop(Core *core) override {
            assert(core);
            assert(m_imageLoader);
            
            core->getGraphicsManager()->unregisterImageLoader(m_imageLoader.get());
        }
        
    private:
        std::unique_ptr<ImageLoaderPNG> m_imageLoader;
    };
}

XE_EXPORT_PLUGIN(xe::Core, xe::PluginPNG)
