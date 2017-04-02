
#pragma once 

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/sg/Renderable.hpp>

namespace xe {
    /**
     * @brief Mesh envelope
     */ 
    struct MeshEnvelope {
        //! Material
        Material *material = nullptr;

        //! Primitive
        Primitive primitive = Primitive::TriangleStrip;

        //! Start Index
        std::size_t start = 0;

        //! End Index
        std::size_t count = 0;
    };
    
    class PhongPipeline;

    /**
     * @brief Geometric mesh class. Used for render static meshes
     */
    class Mesh : public Renderable {
    public:
        explicit Mesh(PhongPipeline *pipeline, SubsetPtr subset);

        explicit Mesh(PhongPipeline *pipeline, std::vector<SubsetPtr> subsets);

        virtual ~Mesh();

        std::size_t getSubsetCount() const;

        Subset* getSubset(const std::size_t index);

        const Subset* getSubset(const std::size_t index) const;

        MeshEnvelope* getEnvelope(const std::size_t subsetIndex);

        const MeshEnvelope* getEnvelope(const std::size_t subsetIndex) const;

        virtual void render() override;

    private:
        PhongPipeline *m_pipeline;
        std::vector<SubsetPtr> m_subsets;
        std::vector<MeshEnvelope> m_envelopes;
    };
}

#endif 
