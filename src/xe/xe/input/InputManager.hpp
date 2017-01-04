
#pragma once 

#ifndef __xe_input_inputmanager__
#define __xe_input_inputmanager__

#include <xe/PreDef.hpp>
#include <xe/input/Keyboard.hpp>
#include <xe/input/Mouse.hpp>

namespace xe {
    class XE_API InputManager {
    public:
        virtual ~InputManager() {}

        /**
         * @brief Get the current keyboard interface
         */
        virtual Keyboard* getKeyboard() = 0;

        /**
         * @brief Get the current mouse interface
         */
        virtual Mouse* getMouse() = 0;

        /**
         * Poll all available devices
         */
        virtual void poll() = 0;
    };
}

#endif 
