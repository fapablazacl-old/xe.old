
#include "Camera.hpp"

#include "PhongPipeline.hpp"

namespace xe {
    Camera::Camera(PhongPipeline *pipeline) 
        : m_pipeline(pipeline) {}

    Camera::~Camera() {}

    void Camera::render() {
        assert(m_pipeline);

        m_pipeline->setTransform(TransformType::Proj, this->getProjMatrix());
        m_pipeline->setTransform(TransformType::View, this->getViewMatrix());
    }
}
