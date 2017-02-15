
#pragma once 

#ifndef __demo_cameracontroller_hpp__
#define __demo_cameracontroller_hpp__

#include <xe/Vector.hpp>
#include "render/Camera.hpp"

#include "Entity.hpp"

namespace demo {

    class AbstractMessage;

    class CameraEntity : public Entity {
    public:
        CameraEntity(xe::LookAtPerspectiveCamera *camera, const float turnSpeed, const float forwardSpeed, const float stepSpeed);

        virtual void update(const float seconds) override;

        virtual void handle(AbstractMessage *message) override;

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
