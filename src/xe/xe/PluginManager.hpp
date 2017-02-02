
#pragma once

#ifndef __xe_pluginmanager_hpp__
#define __xe_pluginmanager_hpp__

#include <string>
#include <map>
#include <xe/PluginData.hpp>

namespace xe {
    template<class Core>
    class PluginManager {
    public:
        virtual ~PluginManager() {}

        /**
         * @brief Get the asocciated core object.
         */
        virtual Core* getCore() = 0;

        /**
         * @brief Load the plugin with the specified name. In case of error, throws an exception.
         */
        virtual void load(const std::string &module) = 0;

        /**
         * @brief Unload the plugin with the specified name. In case of any error, throws an exception.
         */
        virtual void unload(const std::string &module) = 0;

        /**
         * @brief Get the information about all loaded plugins.
         */
        virtual std::map<std::string, xe::PluginData> getLoadedPlugins() const = 0;
    };
}

#endif 
