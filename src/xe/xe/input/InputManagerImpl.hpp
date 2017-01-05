
#pragma once

#ifndef __xe_input_inputmanagerimpl__
#define __xe_input_inputmanagerimpl__

#include <xe/input/InputManager.hpp>

namespace xe {

    /**
     * @brief InputManager base implementation
     */
    class XE_API InputManagerImpl : public InputManager {
    public:
        InputManagerImpl();

        virtual ~InputManagerImpl();

        virtual Keyboard* getKeyboard() override;

        virtual Mouse* getMouse() override;

        virtual void poll() override;

    protected:
        Keyboard *keyboard = nullptr;
        Mouse *mouse = nullptr;
    };
}

#endif 
