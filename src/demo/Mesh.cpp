
#include "Mesh.hpp"

namespace xe { namespace sg {

    Mesh::Mesh(std::vector<xe::gfx::SubsetPtr> subsets) 
        : m_subsets(std::move(subsets)) {
    }

    Mesh::~Mesh() {}

    std::size_t Mesh::getSubsetCount() const {
        return m_subsets.size();
    }

    xe::gfx::Subset* Mesh::getSubset(const std::size_t index) {
        assert(index >= 0);
        assert(index < this->getSubsetCount());

        xe::gfx::Subset* subset = m_subsets[index].get();

        assert(subset);

        return subset;
    }

    const xe::gfx::Subset* Mesh::getSubset(const std::size_t index) const {
        assert(index >= 0);
        assert(index < this->getSubsetCount());

        xe::gfx::Subset* subset = m_subsets[index].get();

        assert(subset);

        return subset;
    }

    Envelope* Mesh::getEnvelope(const std::size_t subsetIndex) {
        assert(subsetIndex >= 0);
        assert(subsetIndex < this->getSubsetCount());

        return &m_envelopes[subsetIndex];
    }

    const Envelope* Mesh::getEnvelope(const std::size_t subsetIndex) const {
        assert(subsetIndex >= 0);
        assert(subsetIndex < this->getSubsetCount());

        return &m_envelopes[subsetIndex];
    }
}}
