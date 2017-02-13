
#pragma once

#ifndef __demo_message_hpp__
#define __demo_message_hpp__

#include <xe/Vector.hpp>

namespace demo {

    class Entity;
    class Message {
    public:
        Message(Entity *source, Entity *destination);

        virtual ~Message() = 0 {}

        Entity* getSource() const;

        Entity* getDestination() const;

    protected:
        Entity *m_source;
        Entity *m_destination;
    };

    template<typename MessageData>
    class AnyMessage : public Message {
    public:
        AnyMessage(Entity *source, Entity *destination, const MessageData &data) 
            : Message(source, destination), m_data(data) {}

        virtual ~AnyMessage() {}

        MessageData getData() const {
            return m_data;
        }

    protected:
        MessageData m_data;
    };
}

#endif
