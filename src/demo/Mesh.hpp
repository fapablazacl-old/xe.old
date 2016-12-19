
#pragma once 

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/Material.hpp>

#include "Renderable.hpp"

namespace xe { namespace sg {

    /**
     * @brief Mesh envelope
     */ 
    class Envelope {
        /*
    public:
        Envelope() {}
        
        Envelope* setMaterial(xe::gfx::Material *material) {
            this->material = material;
            return this;
        }
        
        Envelope* setPrimitive(xe::gfx::Material *material) {
            this->material = material;
            return this;
        }
        
        Envelope* setStart(const std::size_t start) {
            this->start = start;
            return this;
        }
        
        Envelope* setCount(const std::size_t count) {
            this->count = count;
            return this;
        }
        
        const xe::gfx::Material* getMaterial() const {
            return material;
        }
        
        xe::gfx::Material* getMaterial() {
            return material;
        }
        
        xe::gfx::Primitive getPrimitive() const {
            return primitive;
        }
        
        std::size_t getStart() const {
            return start;
        }
        
        std::size_t getCount() const {
            return count;
        }
        
    private:
        */
    public:
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
        Mesh(xe::gfx::SubsetPtr subset);
        Mesh(std::vector<xe::gfx::SubsetPtr> subsets);

        virtual ~Mesh();

        virtual std::type_index getTypeIndex() const override {
            return std::type_index(typeid(Mesh));
        }

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
