
#include "PluginManagerImpl.hpp"

#include <cassert>

namespace xe {
    struct PluginManagerImpl::Private {
        Core *core = nullptr;
        std::map<std::string, std::unique_ptr<Plugin>> plugins;
    };

    PluginManagerImpl::PluginManagerImpl(Core* core) : m_impl(new PluginManagerImpl::Private()) {
        m_impl->core = core;
    }

    PluginManagerImpl::~PluginManagerImpl() {
        delete m_impl;
    }

    Core* PluginManagerImpl::getCore() {
        assert(m_impl);

        return m_impl->core;
    }

    void PluginManagerImpl::load(const std::string &name) {
        assert(m_impl);

        std::string fileName = this->buildPluginFileName(name);

        auto library = std::make_unique<Library>(fileName);
        auto plugin = std::make_unique<PluginLibrary>(std::move(library));
        
        plugin->start(m_impl->core);
            
        m_impl->plugins[name] = std::move(plugin);
    }

    void PluginManagerImpl::unload(const std::string &name) {
        assert(m_impl);

        auto pluginPos = m_impl->plugins.find(name);

        if (pluginPos == m_impl->plugins.end()) {
            // TODO: plugin not found!
        }

        pluginPos->second->stop(m_impl->core);

        m_impl->plugins.erase(pluginPos);
    }

    std::map<std::string, xe::PluginData> PluginManagerImpl::getLoadedPlugins() const {
        assert(m_impl);

        std::map<std::string, xe::PluginData> plugins;
            
        for (const auto &pair : m_impl->plugins) {
            plugins.insert({pair.first, pair.second->getData()});
        }

        return plugins;
    }

    std::string PluginManagerImpl::buildPluginFileName(const std::string &name) {
        assert(m_impl);

#if defined(_WIN32)
        return name + ".dll";
#elif defined(linux)
        return "lib" + name + ".so";
#else 
        return name;
#endif
    }
}
