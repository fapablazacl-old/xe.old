
#pragma once 

#ifndef __demo_system_hpp__
#define __demo_system_hpp__

#include "MessageHandler.hpp"

namespace demo {
    /** 
     * @brief Game submodule.
     */
    class System : public MessageHandler {
    public:
        virtual ~System();

        virtual void update() = 0;
    };
}

#endif 
