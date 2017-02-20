
#pragma once 

#ifndef __xe_input_inputmanager_hpp__
#define __xe_input_inputmanager_hpp__

#include <xe/PreDef.hpp>

namespace xe {
    enum class InputStatus;
    enum class InputCode;

    /**
     * @brief Main interface for input status gathering.
     */
    class XE_API InputManager {
    public:
        virtual ~InputManager();
        
        /**
         * @brief Get the status of the specified input code 
         *
         * The returned status is accurate only if the method 'poll' has been called recently.
         */
        virtual InputStatus getStatus(const InputCode code) const = 0;

        /**
         * @brief Get the status of all connected input devices.
         */
        virtual void poll() = 0;
    };
}

#endif 
