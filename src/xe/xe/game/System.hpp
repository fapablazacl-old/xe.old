
#pragma once 

#ifndef __xe_game_system_hpp__
#define __xe_game_system_hpp__

#include "MessageHandler.hpp"

namespace xe {

    /** 
     * @brief Game submodule.
     */
    class XE_API System : public MessageHandler {
    public:
        virtual ~System();

        virtual void update() = 0;
    };
}

#endif 
