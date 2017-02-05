
#pragma once

#ifndef __xe_core_hpp__
#define __xe_core_hpp__

#include <xe/Version.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/sg/SceneManager.hpp>

#include <iostream>

namespace xe {
    class PluginManager;

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
         * @brief Get the graphics engine manager.
         */
        GraphicsManager* getGraphicsManager();

        /**
         *
         */
        PluginManager* getPluginManager();

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
