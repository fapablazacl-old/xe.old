
#pragma once 

#ifndef __demo_entity_hpp__
#define __demo_entity_hpp__

namespace demo {
    class Message;
    class Entity {
    public:
        virtual ~Entity();

        virtual void update(const float seconds) = 0;

        virtual void handle(Message *message) = 0;
    };
}

#endif
