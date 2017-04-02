
#include "MessageBus.hpp"

#include "Message.hpp"
#include "Entity.hpp"

#include <vector>

namespace xe {
    struct MessageBus::Private {
        std::vector<std::unique_ptr<AbstractMessage>> m_messages;
    };

    MessageBus::MessageBus() 
        : m_impl(new MessageBus::Private()) {}

    MessageBus::~MessageBus() {
        delete m_impl;
    }

    void MessageBus::enqueue(std::unique_ptr<AbstractMessage> message) {
        m_impl->m_messages.push_back(std::move(message));
    }
    
    void MessageBus::dispatch() {
        for (auto &message : m_impl->m_messages) {
            MessageHandler *destination = message->getDestination();
            destination->handle(message.get());
        }

        m_impl->m_messages.clear();
    }
}
