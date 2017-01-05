
#pragma once

#ifndef __xe_core_hpp__
#define __xe_core_hpp__

#include <xe/Version.hpp>
#include <xe/CoreBase.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/sg/SceneManager.hpp>

#include <iostream>

namespace xe {
    
    /**
    * @brief The core class of the engine. 
    * 
    * Holds all the extensible interfaces of the engine.
    */
    class Core : public CoreBase<Core> {
    public:
        Core() {
            std::cout << 
                "The XE C++ engine. \n"
                "Copyright (c) 2016, 2017 Felipe Apablaza\n\n"
                "The license and distribution terms for this library may be\n"
                "found in the file LICENSE in this distribution.\n" << std::endl;
        }

        virtual ~Core() {}

        /** 
         * @brief Get the engine version
         */
        Version getVersion() const {
            return {XE_VERSION_MAJOR, XE_VERSION_MINOR};
        }

        /** 
         * @brief Get the graphics engine manager.
         */
        Manager* getGraphicsManager() {
            return &m_graphicsManager;
        }

    private:
        Manager m_graphicsManager;
    };
}

#endif
