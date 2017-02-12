
#include "CameraController.hpp"

namespace demo {

    CameraController::CameraController(xe::LookAtPerspectiveCamera *camera, const float turnSpeed, const float forwardSpeed, const float stepSpeed) 
        : m_camera(camera), m_turnSpeed(turnSpeed), m_forwardSpeed(forwardSpeed), m_stepSpeed(stepSpeed) {
        assert(camera);
    }

    void CameraController::update(const float seconds) {
        const xe::Vector3f forward = xe::normalize(m_camera->lookAt - m_camera->position);
        const xe::Vector3f step = xe::normalize(xe::cross(forward, m_camera->up));

        const xe::Vector3f moveDelta = (forward*m_currentForwardSpeed + step*m_currentStepSpeed) * seconds;

        m_camera->position += moveDelta;
        m_camera->lookAt += moveDelta;

        m_currentForwardSpeed = 0.0f;
        m_currentStepSpeed = 0.0f;
        m_currentTurnSpeed = 0.0f;
    }

    void CameraController::control(const ControlType controlType) {
        switch (controlType) {

        case ControlType::TurnRight:
            m_currentTurnSpeed = m_turnSpeed;
            break;

        case ControlType::TurnLeft:
            m_currentTurnSpeed = -m_turnSpeed;
            break;

        case ControlType::Forward:
            m_currentForwardSpeed = m_forwardSpeed;
            break;

        case ControlType::Backward:
            m_currentForwardSpeed = -m_forwardSpeed;
            break;

        case ControlType::StepRight:
            m_currentStepSpeed = m_stepSpeed;
            break;

        case ControlType::StepLeft:
            m_currentStepSpeed = -m_stepSpeed;
            break;

        }
    }
}
