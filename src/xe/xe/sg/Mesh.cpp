
#include "Mesh.hpp"

namespace xe { namespace sg {

    struct Mesh::Private {
        std::vector<std::unique_ptr<xe::gfx::Subset>> subsetPtrs;
        std::vector<xe::gfx::Subset*> subsets;
    };

    Mesh::Mesh(std::vector<std::unique_ptr<xe::gfx::Subset>> subsetPtrs) 
        : m_impl(new Mesh::Private()) {

        m_impl->subsetPtrs = std::move(subsetPtrs);

        for (auto &subsetPtr : subsetPtrs) {
            m_impl->subsets.push_back(subsetPtr.get());
        }
    }

    Mesh::~Mesh() {
        delete m_impl;
    }

    std::vector<xe::gfx::Subset*>& Mesh::subsets() {
        assert(m_impl);

        return m_impl->subsets;
    }

    const std::vector<xe::gfx::Subset*>& Mesh::subsets() const {
        assert(m_impl);

        return m_impl->subsets;
    }
}}
