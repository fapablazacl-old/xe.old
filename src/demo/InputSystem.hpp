
#pragma once 

#ifndef __demo_inputsystem_hpp__
#define __demo_inputsystem_hpp__

#include <memory>

#include "System.hpp"

#include <xe/input/InputManager2.hpp>

namespace demo {

    class MessageHandler;
    class MessageBus;

    /**
     * @brief Process messages
     */ 
    class InputSystem : public System {
    public:
        explicit InputSystem(MessageBus *messageBus, xe::InputManager2 *inputManager, MessageHandler *camera);

        virtual ~InputSystem();

        virtual void update() override;

        virtual void handle(AbstractMessage *message) override;

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif 
