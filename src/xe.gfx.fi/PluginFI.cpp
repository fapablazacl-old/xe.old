
#include <xe/Core.hpp>
#include <xe/Plugin.hpp>
#include <cassert>

#include "ImageLoaderFI.hpp"

namespace xe {
    class PluginFI : public xe::Plugin<xe::Core> {
    public:
        PluginFI() {}
        
        ~PluginFI() {}
        
        virtual PluginData getData() const override {
            return {"FreeImage Image Loader", "", {1, 0}};
        }

        virtual void start(Core *core) override {
            assert(core);
            assert(!m_imageLoader);

            m_imageLoader = std::make_unique<ImageLoaderFI>();
            
            core->getGraphicsManager()->registerImageLoader(m_imageLoader.get());
        }

        virtual void stop(Core *core) override {
            assert(core);
            assert(m_imageLoader);
            
            core->getGraphicsManager()->unregisterImageLoader(m_imageLoader.get());
        }
        
    private:
        std::unique_ptr<ImageLoaderFI> m_imageLoader;
    };
}

XE_EXPORT_PLUGIN(xe::Core, xe::PluginFI)
