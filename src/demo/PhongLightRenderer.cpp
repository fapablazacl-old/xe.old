
#include "PhongLightRenderer.hpp"
#include "PhongLight.hpp"

namespace xe { 

    PhongLightRenderer::PhongLightRenderer(xe::GraphicsDevice *device) : m_device(device) {
        assert(device);
    }

    PhongLightRenderer::~PhongLightRenderer() {}

    void PhongLightRenderer::render(Renderable *renderable) {
        assert(m_device);
        assert(renderable);
        assert(dynamic_cast<PhongLight*>(renderable));

        auto light = static_cast<PhongLight*>(renderable);

        light->render(m_device);
    }
}
