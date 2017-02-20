
#include "InputSystem.hpp"

#include <map>
#include <cassert>
#include <xe/input/InputCode.hpp>
#include <xe/input/InputStatus.hpp>


#include "MoveType.hpp"
#include "MessageBus.hpp"
#include "MessageHandler.hpp"

namespace demo {

    struct InputSystem::Private {
        MessageBus *messageBus = nullptr;
        xe::InputManager2 *manager = nullptr;
        MessageHandler *cameraEntity = nullptr;

        std::map<xe::InputCode, MoveType> m_inputCodeToMoveType = {
            {xe::InputCode::KeyLeft, MoveType::StepLeft}, 
            {xe::InputCode::KeyRight, MoveType::StepRight}, 
            {xe::InputCode::KeyUp, MoveType::Forward}, 
            {xe::InputCode::KeyDown, MoveType::Backward}
        };
    };

    InputSystem::InputSystem(MessageBus *messageBus, xe::InputManager2 *inputManager, MessageHandler *cameraEntity) 
        : m_impl(new InputSystem::Private()) {

        m_impl->messageBus = messageBus;
        m_impl->manager = inputManager;
        m_impl->cameraEntity = cameraEntity;
    }

    InputSystem::~InputSystem() {}

    void InputSystem::update()  {
        assert(m_impl);

        m_impl->manager->poll();

        if (m_impl->manager->getStatus(xe::InputCode::KeyEsc) == xe::InputStatus::Press) {
            // TODO: Issue exit message
        }

        for (const auto &pair : m_impl->m_inputCodeToMoveType) {
            if (m_impl->manager->getStatus(pair.first) == xe::InputStatus::Press) {
                m_impl->messageBus->enqueue(nullptr, m_impl->cameraEntity, pair.second);
            }
        }
    }

    void InputSystem::handle(AbstractMessage *message) {}
}
