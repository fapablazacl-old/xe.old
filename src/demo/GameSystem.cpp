
#include "GameSystem.hpp"

#include <vector>

#include "Entity.hpp"
#include "MessageBus.hpp"

namespace demo {
    struct GameState::Private {
        std::vector<std::unique_ptr<Entity>> m_entities;
        MessageBus m_messageBus;

        xe::InputManager *inputManager = nullptr;
    };

    GameState::GameState(xe::InputManager *inputManager) 
        : m_impl(new GameState::Private()) {}

    GameState::~GameState() {}

    void GameState::run() {

    }
}
