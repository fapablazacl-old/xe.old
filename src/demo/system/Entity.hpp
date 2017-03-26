
#pragma once 

#ifndef __demo_entity_hpp__
#define __demo_entity_hpp__

#include "MessageHandler.hpp"

namespace demo {
    class Entity : public MessageHandler {
    public:
        virtual ~Entity();

        virtual void update(const float seconds) = 0;
    };
}

#endif
