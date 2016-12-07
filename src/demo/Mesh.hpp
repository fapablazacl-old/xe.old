
#pragma once 

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <map>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/Material.hpp>

namespace xe { namespace sg {
    /**
     * @brief Geometric mesh class. Used for render static meshes
     */
    class Mesh {
    public:
        Mesh(std::vector<xe::gfx::SubsetPtr> subsets);

        ~Mesh();

        std::size_t getSubsetCount() const;

        xe::gfx::Subset* getSubset(const std::size_t index);

        const xe::gfx::Subset* getSubset(const std::size_t index) const;

        void setSubsetMaterial(const std::size_t index, xe::gfx::Material* material);

        xe::gfx::Material* getSubsetMaterial(const std::size_t index) const;

    private:
        std::vector<xe::gfx::SubsetPtr> m_subsets;
        std::map<const xe::gfx::Subset*, xe::gfx::Material*> m_subsetMaterial;
    };
}}

#endif 
