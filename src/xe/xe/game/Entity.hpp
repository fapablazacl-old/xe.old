
#pragma once 

#ifndef __xe_game_entity_hpp__
#define __xe_game_entity_hpp__

#include "MessageHandler.hpp"

namespace xe {
    class XE_API Entity : public MessageHandler {
    public:
        virtual ~Entity();

        virtual void update(const float seconds) = 0;
    };
}

#endif
