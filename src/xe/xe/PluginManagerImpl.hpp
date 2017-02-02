
#pragma once

#ifndef __xe_pluginmanagerimpl_hpp__
#define __xe_pluginmanagerimpl_hpp__

#include <xe/Library.hpp>
#include <xe/Plugin.hpp>
#include <xe/PluginLibrary.hpp>
#include <xe/PluginManager.hpp>

#include <memory>
#include <map>

namespace xe {
    template<class Core>
    class PluginManagerImpl : public PluginManager<Core> {
    public:
        explicit PluginManagerImpl(Core* core) 
            : m_core(core) {}

        virtual ~PluginManagerImpl() {}

        virtual Core* getCore() override {
            return m_core;
        }

        virtual void load(const std::string &name) override {
            std::string fileName = this->buildPluginFileName(name);

            auto library = std::make_unique<Library>(fileName);
            auto plugin = std::make_unique<PluginLibrary<Core>>(std::move(library));
        
            plugin->start(m_core);
            
            m_plugins[name] = std::move(plugin);
        }

        virtual void unload(const std::string &name) override {
            auto pluginPos = m_plugins.find(name);

            if (pluginPos == m_plugins.end()) {
                // TODO: plugin not found!
            }

            pluginPos->second->stop(m_core);

            m_plugins.erase(pluginPos);
        }

        virtual std::map<std::string, xe::PluginData> getLoadedPlugins() const override {
            std::map<std::string, xe::PluginData> plugins;
            
            for (const auto &pair : m_plugins) {
                plugins.insert({pair.first, pair.second->getData()});
            }

            return plugins;
        }

    private:
        std::string buildPluginFileName(const std::string &name) {
#if defined(_WIN32)
            return name + ".dll";
#elif defined(linux)
            return "lib" + name + ".so";
#else 
            return name;
#endif
        }

    private:
        Core *m_core = nullptr;
        std::map<std::string, std::unique_ptr<Plugin<Core>>> m_plugins;
    };
}

#endif 
