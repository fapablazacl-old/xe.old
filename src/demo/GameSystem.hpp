
#pragma once 

#ifndef __demo_gamestate_hpp__
#define __demo_gamestate_hpp__

#include <memory>

#include <xe/input/InputManager2.hpp>

namespace demo {
    class GameState {
    public:
        GameState(xe::InputManager2 *inputManager);

        ~GameState();

        void run();

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif 
