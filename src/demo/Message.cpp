
#include "Message.hpp"

namespace demo {
    Message::Message(Entity *source, Entity *destination) : m_source(source), m_destination(destination) {
    }

    Entity* Message::getSource() const {
        return m_source;
    }

    Entity* Message::getDestination() const {
        return m_destination;
    }
}
