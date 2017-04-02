
#include "Mesh.hpp"

#include "PhongPipeline.hpp"

namespace xe {

    Mesh::Mesh(PhongPipeline *pipeline, xe::SubsetPtr subset) : m_pipeline(pipeline) {
        m_subsets.push_back(std::move(subset));

        m_envelopes.resize(m_subsets.size());
    }

    Mesh::Mesh(PhongPipeline *pipeline, std::vector<xe::SubsetPtr> subsets) 
            : m_pipeline(pipeline), m_subsets(std::move(subsets)) {
        m_envelopes.resize(m_subsets.size());
    }

    Mesh::~Mesh() {}

    std::size_t Mesh::getSubsetCount() const {
        return m_subsets.size();
    }

    xe::Subset* Mesh::getSubset(const std::size_t index) {
        assert(index >= 0);
        assert(index < this->getSubsetCount());

        xe::Subset* subset = m_subsets[index].get();

        assert(subset);

        return subset;
    }

    const xe::Subset* Mesh::getSubset(const std::size_t index) const {
        assert(index >= 0);
        assert(index < this->getSubsetCount());

        xe::Subset* subset = m_subsets[index].get();

        assert(subset);

        return subset;
    }

    MeshEnvelope* Mesh::getEnvelope(const std::size_t subsetIndex) {
        assert(subsetIndex >= 0);
        assert(subsetIndex < this->getSubsetCount());

        return &m_envelopes[subsetIndex];
    }

    const MeshEnvelope* Mesh::getEnvelope(const std::size_t subsetIndex) const {
        assert(subsetIndex >= 0);
        assert(subsetIndex < this->getSubsetCount());

        return &m_envelopes[subsetIndex];
    }

    void Mesh::render() {
        auto device = m_pipeline->getDevice();

        for (std::size_t i=0; i<this->getSubsetCount(); i++) {
            xe::Subset *subset = this->getSubset(i);
            xe::MeshEnvelope *envelope = this->getEnvelope(i);

            assert(subset);
            assert(envelope);
            assert(envelope->start >= 0);
            assert(envelope->count > 0);

            device->setMaterial(envelope->material);
            device->setSubset(subset);
            device->draw({envelope->primitive, envelope->count, envelope->start});
        }
    }
}
