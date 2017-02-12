
#include "CameraRenderer.hpp"
#include "Camera.hpp"

#include <cassert>

namespace xe {

    CameraRenderer::CameraRenderer(PhongPipeline *pipeline) : m_pipeline(pipeline) {
        assert(pipeline);
    }

    CameraRenderer::~CameraRenderer() {}

    void CameraRenderer::render(Renderable *renderable) {
        assert(m_pipeline);
        assert(renderable);
        assert(dynamic_cast<Camera*>(renderable));

        auto camera = static_cast<Camera*>(renderable);

        m_pipeline->setTransform(TransformType::Proj, camera->getProjMatrix());
        m_pipeline->setTransform(TransformType::View, camera->getViewMatrix());
    }
}
