
#pragma once 

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/Material.hpp>

#include "Renderable.hpp"

namespace xe { namespace sg {

    struct Envelope {
        xe::gfx::Material *material = nullptr;

        xe::gfx::Primitive primitive = xe::gfx::Primitive::TriangleStrip;

        std::size_t start = 0;
        std::size_t count = 0;
    };

    /**
     * @brief Geometric mesh class. Used for render static meshes
     */
    class Mesh : public Renderable {
    public:
        Mesh(std::vector<xe::gfx::SubsetPtr> subsets);

        ~Mesh();

        std::size_t getSubsetCount() const;

        xe::gfx::Subset* getSubset(const std::size_t index);

        const xe::gfx::Subset* getSubset(const std::size_t index) const;

        Envelope* getEnvelope(const std::size_t subsetIndex);

        const Envelope* getEnvelope(const std::size_t subsetIndex) const;

    private:
        std::vector<xe::gfx::SubsetPtr> m_subsets;
        std::vector<Envelope> m_envelopes;
    };
}}

#endif 
