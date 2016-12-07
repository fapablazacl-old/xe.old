
#pragma once

#ifndef __xe_gfx_subsetsubset__
#define __xe_gfx_subsetsubset__

#include <map>
#include <xe/Buffer.hpp>
#include <xe/DataFormat.hpp>

#include <xe/gfx/SubsetFormat.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Abstract geometry mesh subset interface
     */
    class XE_API Subset {
    public:
        virtual ~Subset() {}

        /**
         * @brief Get the format of the mesh.
         */
        virtual const SubsetFormat* getFormat() const = 0;

        virtual std::size_t getBufferCount() const = 0;
        virtual Buffer* getBuffer(const std::size_t index) = 0;
        virtual const Buffer* getBuffer(const std::size_t index) const = 0;
    };

    typedef std::unique_ptr<Subset> SubsetPtr;
}}

#endif 
