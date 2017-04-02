
#pragma once

#ifndef __xe_game_messagebus_hpp__
#define __xe_game_messagebus_hpp__

#include <memory>

#include "Message.hpp"

namespace xe {
    class XE_API MessageBus {
    public:
        MessageBus();

        ~MessageBus();

        void enqueue(std::unique_ptr<AbstractMessage> message);
        
        void dispatch();

        template<typename MessageData>
        void enqueue(MessageHandler *source, MessageHandler *destination, const MessageData &data) {
            this->enqueue(std::make_unique<Message<MessageData>>(source, destination, data));
        }

    private:
        struct Private;
        Private* m_impl;
    };
}

#endif
