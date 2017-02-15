
#pragma once

#ifndef __demo_messagebus_hpp__
#define __demo_messagebus_hpp__

#include <memory>

namespace demo {

    class AbstractMessage;
    class MessageBus {
    public:
        MessageBus();

        ~MessageBus();

        void enqueue(std::unique_ptr<AbstractMessage> message);
        
        void dispatch();

        template<typename Message, typename ...Args>
        void enqueue(Args... args) {
            this->enqueue(std::make_unique<Message>());
        }

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
