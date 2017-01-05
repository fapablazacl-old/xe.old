
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
    class Envelope {
        /*
    public:
        Envelope() {}
        
        Envelope* setMaterial(xe::Material *material) {
            this->material = material;
            return this;
        }
        
        Envelope* setPrimitive(xe::Material *material) {
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
        
        const xe::Material* getMaterial() const {
            return material;
        }
        
        xe::Material* getMaterial() {
            return material;
        }
        
        xe::Primitive getPrimitive() const {
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
        Material *material = nullptr;
        Primitive primitive = Primitive::TriangleStrip;

        std::size_t start = 0;
        std::size_t count = 0;
    };
    
    /**
     * @brief Geometric mesh class. Used for render static meshes
     */
    class Mesh : public Renderable {
    public:
        Mesh(SubsetPtr subset);
        Mesh(std::vector<SubsetPtr> subsets);

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
