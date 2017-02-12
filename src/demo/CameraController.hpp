
#pragma once 

#ifndef __demo_cameracontroller_hpp__
#define __demo_cameracontroller_hpp__

#include <xe/Vector.hpp>
#include "render/Camera.hpp"

namespace demo {

    enum class ControlType {
        Forward, 
        Backward, 
        StepLeft,
        StepRight,
        TurnLeft, 
        TurnRight
    };

    class CameraController {
    public:
        CameraController(xe::LookAtPerspectiveCamera *camera, const float turnSpeed, const float forwardSpeed, const float stepSpeed);

        void update(const float seconds);

        void control(const ControlType controlType);

    private:
        xe::LookAtPerspectiveCamera *m_camera;
        const float m_turnSpeed;
        const float m_forwardSpeed;
        const float m_stepSpeed;

        float m_currentTurnSpeed = 0.0f;
        float m_currentForwardSpeed = 0.0f;
        float m_currentStepSpeed = 0.0f;
    };
}

#endif
