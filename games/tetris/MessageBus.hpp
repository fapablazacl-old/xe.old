
#pragma once

#ifndef __tetris_messagebus_hpp__
#define __tetris_messagebus_hpp__

#include <memory>

namespace tetris {

    struct Message {
        enum Enum {
            GameStart, 
            GameExit, 
            GamePause, 
            GameResume,

            ConsoleShow, 
            ConsoleHide, 

            FigureMoveLeft,
            FigureMoveRight,
            FigureMoveDown,
            FigureFall,
            FigureHit,
            FigureMerge, 
            FigureSpawn, 
            FigurePreview, 

            PlayerWin, 
            PlayerLose, 
        };

        explicit Message(const Enum type) : m_type(type) {}

        Enum getType() const {
            return m_type;
        }

    private:
        Enum m_type;
    };

    class MessageBus {
    public:
        virtual ~MessageBus() {}

        virtual void postMessage(const Message &message) = 0;

    public:
        static std::unique_ptr<MessageBus> new_();
    };
}

#endif
