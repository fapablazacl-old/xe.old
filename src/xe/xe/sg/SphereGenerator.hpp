
#pragma once 

#ifndef __xe_sg_spheregenerator_hpp__
#define __xe_sg_spheregenerator_hpp__

#include <cstdint>
#include <vector>

#include <xe/PreDef.hpp>
#include <xe/Vector.hpp>
#include <xe/sg/Plane.hpp>

namespace xe {
    struct XE_API SphereGenerator {
        std::size_t slices = 4;
        std::size_t stacks = 5;
    
        SphereGenerator() {}
    
        SphereGenerator(const std::size_t slices_, const std::size_t stacks_)
            : slices(slices_), stacks(stacks_) {}
    
        std::size_t getCoordCount() const;
    
        std::vector<xe::Vector3f> genCoords(const float radius) const;
    
        std::vector<std::uint32_t> genIndices() const;
    
        /**
         * @brief Generate the normal for any ellipsoid object (including spheres)
         */
        std::vector<xe::Vector3f> genNormals(const std::vector<xe::Vector3f> &coords) const;
        
        std::vector<xe::Vector2f> genTexCoords(const std::vector<xe::Vector3f> &normals) const;
    };
}

#endif
