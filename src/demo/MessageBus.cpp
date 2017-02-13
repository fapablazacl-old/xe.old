
#include "MessageBus.hpp"

#include "Message.hpp"
#include "Entity.hpp"

#include <vector>

namespace demo {
    struct MessageBus::Private {
        std::vector<std::unique_ptr<Message>> m_messages;
    };

    MessageBus::MessageBus() : m_impl(new MessageBus::Private()) {
    }

    MessageBus::~MessageBus() {}

    void MessageBus::enqueue(std::unique_ptr<Message> message) {
        m_impl->m_messages.push_back(std::move(message));
    }
    
    void MessageBus::dispatch() {
        for (auto &message : m_impl->m_messages) {
            Entity *destination = message->getDestination();
            destination->handle(message.get());
        }

        m_impl->m_messages.clear();
    }
}
