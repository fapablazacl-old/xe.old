
#pragma once 

#ifndef __demo_messagehandler_hpp__
#define __demo_messagehandler_hpp__

namespace demo {
    class AbstractMessage;
    class MessageHandler {
    public:
        virtual ~MessageHandler();
        virtual void handle(AbstractMessage *message) = 0;
    };
}


#endif
