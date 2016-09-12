
#pragma once

#ifndef __EXENG_CORE_HPP__
#define __EXENG_CORE_HPP__

#include <xe/Version.hpp>

#include <xe/sys/PluginManager.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/sg/SceneManager.hpp>

namespace xe {
    
    /**
    * @brief The core class of the engine. 
    * 
    * Holds all the extensible interfaces of the engine.
    */
    class XE_API Core {
    public:
        Core();
        virtual ~Core();

        /** 
         * @brief Get the engine version
         */
        Version getVersion() const;

        /**
         * @brief Get the plugin engine manager.
         */
        xe::sys::PluginManager* getPluginManager() {
            return &m_pluginManager;
        }

        /** 
         * @brief Get the graphics engine manager.
         */
        xe::gfx::Manager* getGraphicsManager() {
            return &m_graphicsManager;
        }

    private:
        xe::sys::PluginManager m_pluginManager;
        xe::gfx::Manager m_graphicsManager;
    };
}

#endif
