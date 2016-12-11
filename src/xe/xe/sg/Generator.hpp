
#pragma once

#ifndef __xe_sg_generator_hpp__
#define __xe_sg_generator_hpp__

#include <xe/PreDef.hpp>
#include <xe/Math.hpp>
#include <xe/Vector.hpp>
#include <vector>

namespace xe { namespace sg {

    struct XE_API Generator {
        /**
         * @brief Default normal generator.
         */
        std::vector<xe::Vector3f> genNormals(const std::vector<xe::Vector3f> &coords) const;
    };


    struct XE_API SphereGenerator {
        std::size_t slices = 4;
        std::size_t stacks = 5;

        SphereGenerator() {}

        SphereGenerator(const std::size_t slices_, const std::size_t stacks_)
            : slices(slices_), stacks(stacks_) {}

        std::vector<xe::Vector3f> genCoords(const float radius) const;

        std::vector<std::uint32_t> genIndices() const;

        /**
         * @brief Generate the normal for any ellipsoid object (including spheres)
         */
        std::vector<xe::Vector3f> genNormals(const std::vector<xe::Vector3f> &coords) const;
    };
}}

#endif
