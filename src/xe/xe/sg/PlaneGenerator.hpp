
#pragma once 

#ifndef __xe_sg_planegenerator_hpp__
#define __xe_sg_planegenerator_hpp__

#include <cstdint>
#include <vector>

#include <xe/PreDef.hpp>
#include <xe/math/Vector.hpp>
#include <xe/math/Plane.hpp>

namespace xe {
    struct XE_API PlaneGenerator {
        std::size_t slices = 1;
        std::size_t stacks = 1;
    
        PlaneGenerator() {}
    
        PlaneGenerator(const std::size_t slices_, const std::size_t stacks_)
            : slices(slices_), stacks(stacks_) {}
    
        std::vector<xe::Vector3f> genCoords(const Plane_f &plane, const float width, const float length) const;
    
        std::size_t getCoordCount() const;
    
        std::vector<std::uint32_t> genIndices() const;
    
        std::vector<xe::Vector3f> genNormals(const Plane_f &plane) const;
        
        std::vector<xe::Vector2f> genTexCoords() const;
    };
}

#endif 
