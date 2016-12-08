
#include "MeshRenderer.hpp"
#include "Mesh.hpp"

namespace xe { namespace sg {  

    MeshRenderer::MeshRenderer(xe::gfx::Device *device) : m_device(device) {
        assert(device);
    }

    MeshRenderer::~MeshRenderer() {}

    void MeshRenderer::render(Renderable *renderable) {
        assert(m_device);
        assert(renderable);
        assert(dynamic_cast<Mesh*>(renderable));

        auto mesh = static_cast<Mesh*>(renderable);

        for (std::size_t i=0; i<mesh->getSubsetCount(); i++) {
            xe::gfx::Subset *subset = mesh->getSubset(i);
            xe::sg::Envelope *envelope = mesh->getEnvelope(i);

            assert(envelope);

            // TODO: Think for another method for render materials
            envelope->material->render(m_device);

            m_device->setMesh(subset);
            m_device->draw(envelope->primitive, envelope->start, envelope->count);
        }
    }
}}
