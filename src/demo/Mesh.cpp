
#include "Mesh.hpp"

namespace xe { namespace sg {

    Mesh::Mesh(std::vector<xe::gfx::SubsetPtr> subsets) 
        : m_subsets(std::move(subsets)) {}

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

    void Mesh::setSubsetMaterial(const std::size_t index, xe::gfx::Material* material) {
        assert(index >= 0);
        assert(index < this->getSubsetCount());
        assert(material);

        xe::gfx::Subset* subset = this->getSubset(index);

        m_subsetMaterial[subset] = material;
    }

    xe::gfx::Material* Mesh::getSubsetMaterial(const std::size_t index) const {
        assert(index >= 0);
        assert(index < this->getSubsetCount());

        const xe::gfx::Subset* subset = this->getSubset(index);
        const auto subsetMaterialIt = m_subsetMaterial.find(subset);

        if (subsetMaterialIt == m_subsetMaterial.end()) {
            return nullptr;
        } else {
            subsetMaterialIt->second;
        }
    }
}}
