
#include "PluginPNG.hpp"
#include "ImageLoaderPNG.hpp"

#include <xe/Core.hpp>
#include <cassert>

namespace xe {
    struct PluginPNG::Private {
        ImageLoaderPNG m_loader;
    };

    PluginPNG::PluginPNG() 
        : m_impl(new PluginPNG::Private()) {}

    PluginPNG::~PluginPNG() {}

    PluginData PluginPNG::getData() const {
        return {"lodepng based Image Loader", "", {1, 0}};
    }

    void PluginPNG::start(Core *core) {
        assert(core);
        assert(!m_impl);
    
        core->getGraphicsManager()->registerImageLoader(&m_impl->m_loader);
    }

    void PluginPNG::stop(Core *core) {
        assert(core);
        assert(!m_impl);
            
        core->getGraphicsManager()->unregisterImageLoader(&m_impl->m_loader);
    }
}

#if defined(XE_PLUGIN_DYNAMIC_LINKING)
XE_EXPORT_PLUGIN(xe::Core, xe::PluginPNG)
#endif
