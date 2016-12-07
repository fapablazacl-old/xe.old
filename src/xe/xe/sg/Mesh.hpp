
#pragma once

#ifndef __xe_sg_mesh_hpp__
#define __xe_sg_mesh_hpp__

#include <vector>
#include <xe/PreDef.hpp>
#include <xe/gfx/SubsetFormat.hpp>
#include <xe/gfx/Subset.hpp>

namespace xe { namespace sg {
    /**
     * @brief Geometric mesh definition. Mesh subset collection.
     */
    class XE_API Mesh {
    public:
        Mesh(std::vector<std::unique_ptr<xe::gfx::Subset>> subsets);

        ~Mesh();

        std::vector<xe::gfx::Subset*>& subsets();

        const std::vector<xe::gfx::Subset*>& subsets() const;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}}

#endif 
