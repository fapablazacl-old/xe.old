
#include "PluginLibrary.hpp"

#include <xe/Plugin.hpp>

namespace xe {

    struct PluginLibrary::Private {
        std::unique_ptr<Library> library;
        std::unique_ptr<Plugin> plugin;
    };

    PluginLibrary::PluginLibrary(std::unique_ptr<Library> library) : m_impl(new PluginLibrary::Private()) {

        m_impl->library = std::move(library);

        auto createPluginAddress = m_impl->library->getAddress(XE_GET_PLUGIN_OBJECT_NAME_STR);
        auto createPlugin = (Plugin* (*)()) createPluginAddress;
        
        m_impl->plugin = std::unique_ptr<Plugin>(createPlugin());
    }

    PluginLibrary::~PluginLibrary() {}
        
    PluginData PluginLibrary::getData() const {
        return m_impl->plugin->getData();
    }

    void PluginLibrary::start(Core *core) {
        m_impl->plugin->start(core);
    }

    void PluginLibrary::stop(Core *core) {
        m_impl->plugin->stop(core);
    }
}
