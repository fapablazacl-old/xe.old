
#pragma once 

#ifndef __xe_game_messagehandler_hpp__
#define __xe_game_messagehandler_hpp__

#include "xe/PreDef.hpp"

namespace xe {
    class XE_API AbstractMessage;
    class XE_API MessageHandler {
    public:
        virtual ~MessageHandler();

        virtual void handle(AbstractMessage *message) = 0;
    };
}

#endif
