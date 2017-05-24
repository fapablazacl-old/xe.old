
#include "Message.hpp"

namespace demo {
    AbstractMessage::AbstractMessage(MessageHandler *source, MessageHandler *destination) : m_source(source), m_destination(destination) {
    }

    MessageHandler* AbstractMessage::getSource() const {
        return m_source;
    }

    MessageHandler* AbstractMessage::getDestination() const {
        return m_destination;
    }
}
