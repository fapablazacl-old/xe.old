
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
    class XE_API PluginManagerImpl : public PluginManager {
    public:
        explicit PluginManagerImpl(Core* core);

        virtual ~PluginManagerImpl();

        virtual Core* getCore() override;

        virtual void load(const std::string &name) override;

        virtual void unload(const std::string &name) override;

        virtual std::map<std::string, xe::PluginData> getLoadedPlugins() const override;

    private:
        std::string buildPluginFileName(const std::string &name);

    private:
        struct Private;
        Private *m_impl;
    };
}

#endif 
