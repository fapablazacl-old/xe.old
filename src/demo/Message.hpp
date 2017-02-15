
#pragma once

#ifndef __demo_message_hpp__
#define __demo_message_hpp__

#include <xe/Vector.hpp>

namespace demo {

    class MessageHandler;
    class AbstractMessage {
    public:
        AbstractMessage(MessageHandler *source, MessageHandler *destination);

        virtual ~AbstractMessage() = 0 {}

        MessageHandler* getSource() const;

        MessageHandler* getDestination() const;

    protected:
        MessageHandler *m_source;
        MessageHandler *m_destination;
    };

    template<typename MessageData>
    class Message : public AbstractMessage {
    public:
        Message(MessageHandler *source, MessageHandler *destination, const MessageData &data) 
            : AbstractMessage(source, destination), m_data(data) {}

        virtual ~Message() {}

        MessageData getData() const {
            return m_data;
        }

    protected:
        MessageData m_data;
    };
}

#endif
