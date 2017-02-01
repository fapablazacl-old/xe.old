
#pragma once

#ifndef __xe_pluginlibrary_hpp__
#define __xe_pluginlibrary_hpp__

#include <string>
#include <memory>

#include <xe/Library.hpp>
#include <xe/Plugin.hpp>

namespace xe { 

    template<class Core>
    class PluginLibrary : public Plugin<Core> {
    public:
        explicit PluginLibrary(std::unique_ptr<Library> library) {
            m_library = std::move(library);

            auto createPluginAddress = m_library->getAddress(XE_GET_PLUGIN_OBJECT_NAME_STR);
            auto createPlugin = (Plugin<Core>* (*)()) createPluginAddress;
            
            m_plugin = std::unique_ptr<Plugin<Core>>(createPlugin());
        }

        virtual ~PluginLibrary() {}
        
        virtual PluginData getData() const override {
            return m_plugin->getData();
        }

        virtual void start(Core *core) override {
            m_plugin->start(core);
        }

        virtual void stop(Core *core) override {
            m_plugin->stop(core);
        }

    private:
        std::unique_ptr<Library> m_library;
        std::unique_ptr<Plugin<Core>> m_plugin;
    };
}

#endif 
