
#pragma once 

#ifndef __tetris_system_hpp__
#define __tetris_system_hpp__

namespace tetris {
    struct Message;

    class MessageBus;
    class System {
    public:
        explicit System(MessageBus *messageBus);

        virtual ~System();

        virtual void handle(const Message *msg) = 0;

        virtual void update() = 0;

    private:
        MessageBus *m_messageBus;
    };
}

#endif 
