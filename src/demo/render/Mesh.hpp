
#pragma once 

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/Material.hpp>

#include "Renderable.hpp"

namespace xe {

    /**
     * @brief Mesh envelope
     */ 
    struct Envelope {
        //! Material
        Material *material = nullptr;

        //! Primitive
        Primitive primitive = Primitive::TriangleStrip;

        //! Start Index
        std::size_t start = 0;

        //! End Index
        std::size_t count = 0;
    };
    
    /**
     * @brief Geometric mesh class. Used for render static meshes
     */
    class Mesh : public Renderable {
    public:
        explicit Mesh(SubsetPtr subset);

        explicit Mesh(std::vector<SubsetPtr> subsets);

        virtual ~Mesh();

        virtual std::type_index getTypeIndex() const override {
            return std::type_index(typeid(Mesh));
        }

        std::size_t getSubsetCount() const;

        Subset* getSubset(const std::size_t index);

        const Subset* getSubset(const std::size_t index) const;

        Envelope* getEnvelope(const std::size_t subsetIndex);

        const Envelope* getEnvelope(const std::size_t subsetIndex) const;

    private:
        std::vector<SubsetPtr> m_subsets;
        std::vector<Envelope> m_envelopes;
    };
}

#endif 
