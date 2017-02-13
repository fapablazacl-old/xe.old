
#include "CameraEntity.hpp"

#include "MoveMessage.hpp"

namespace demo {

    CameraEntity::CameraEntity(xe::LookAtPerspectiveCamera *camera, const float turnSpeed, const float forwardSpeed, const float stepSpeed) 
        : m_camera(camera), m_turnSpeed(turnSpeed), m_forwardSpeed(forwardSpeed), m_stepSpeed(stepSpeed) {
        assert(camera);
    }

    void CameraEntity::update(const float seconds) {
        const xe::Vector3f forward = xe::normalize(m_camera->lookAt - m_camera->position);
        const xe::Vector3f step = xe::normalize(xe::cross(forward, m_camera->up));

        const xe::Vector3f moveDelta = (forward*m_currentForwardSpeed + step*m_currentStepSpeed) * seconds;

        m_camera->position += moveDelta;
        m_camera->lookAt += moveDelta;

        m_currentForwardSpeed = 0.0f;
        m_currentStepSpeed = 0.0f;
        m_currentTurnSpeed = 0.0f;
    }

    void CameraEntity::handle(Message *message) {
        assert(message);
        assert(message->getDestination() == this);

        if (MoveMessage *moveMessage = dynamic_cast<MoveMessage *>(message)) {
            MoveType moveType = moveMessage->getData();

            switch (moveType) {
                case MoveType::TurnRight: m_currentTurnSpeed = m_turnSpeed; break;
                case MoveType::TurnLeft: m_currentTurnSpeed = -m_turnSpeed; break;
                case MoveType::Forward: m_currentForwardSpeed = m_forwardSpeed; break;
                case MoveType::Backward: m_currentForwardSpeed = -m_forwardSpeed; break;
                case MoveType::StepRight: m_currentStepSpeed = m_stepSpeed; break;
                case MoveType::StepLeft: m_currentStepSpeed = -m_stepSpeed; break;
            }
        }
    }
}
