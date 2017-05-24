
#pragma once

#ifndef __demo_messagebus_hpp__
#define __demo_messagebus_hpp__

#include <memory>

#include "Message.hpp"

namespace demo {

    class MessageBus {
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
        std::unique_ptr<Private> m_impl;
    };
}

#endif
