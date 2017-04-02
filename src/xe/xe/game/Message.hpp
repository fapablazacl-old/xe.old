
#pragma once

#ifndef __xe_game_message_hpp__
#define __xe_game_message_hpp__

#include "xe/PreDef.hpp"
#include "xe/math/Vector.hpp"

namespace xe {
    class XE_API MessageHandler;
    class XE_API AbstractMessage {
    public:
        AbstractMessage(MessageHandler *source, MessageHandler *destination);

        virtual ~AbstractMessage() {}

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
