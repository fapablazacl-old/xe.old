
#include "GameSystem.hpp"

#include <vector>

#include "Entity.hpp"
#include "MessageBus.hpp"

namespace demo {
    struct GameState::Private {
        std::vector<std::unique_ptr<Entity>> m_entities;
        MessageBus m_messageBus;

        xe::InputManager2 *inputManager = nullptr;
    };

    GameState::GameState(xe::InputManager2 *inputManager) 
        : m_impl(new GameState::Private()) {}

    GameState::~GameState() {}

    void GameState::run() {

    }
}
