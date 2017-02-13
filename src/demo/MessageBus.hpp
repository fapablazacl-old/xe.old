
#pragma once

#ifndef __demo_messagebus_hpp__
#define __demo_messagebus_hpp__

#include <memory>

namespace demo {

    class Message;
    class MessageBus {
    public:
        MessageBus();

        ~MessageBus();

        void enqueue(std::unique_ptr<Message> message);
        
        void dispatch();

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
