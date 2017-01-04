
#include "MeshRenderer.hpp"
#include "Mesh.hpp"

namespace xe {

    MeshRenderer::MeshRenderer(xe::GraphicsDevice *device) : m_device(device) {
        assert(device);
    }

    MeshRenderer::~MeshRenderer() {}

    void MeshRenderer::render(Renderable *renderable) {
        assert(m_device);
        assert(renderable);
        assert(dynamic_cast<Mesh*>(renderable));

        auto mesh = static_cast<Mesh*>(renderable);

        for (std::size_t i=0; i<mesh->getSubsetCount(); i++) {
            xe::Subset *subset = mesh->getSubset(i);
            xe::Envelope *envelope = mesh->getEnvelope(i);

            assert(subset);
            assert(envelope);
            assert(envelope->start >= 0);
            assert(envelope->count > 0);
            
            m_device->setMaterial(envelope->material);
            m_device->setMesh(subset);
            m_device->draw(envelope->primitive, envelope->start, envelope->count);
        }
    }
}
