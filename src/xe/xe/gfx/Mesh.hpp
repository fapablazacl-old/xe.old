
#pragma once

#ifndef __xe_gfx_subset__
#define __xe_gfx_subset__

#include <xe/Buffer.hpp>
#include <xe/DataFormat.hpp>
#include <xe/gfx/MeshFormat.hpp>
#include <map>

namespace xe { namespace gfx {

    /**
     * @brief Abstract geometry mesh interface
     */
    class XE_API Mesh {
    public:
        virtual ~Mesh() {}

        virtual const MeshFormat* getFormat() const = 0;

        virtual std::size_t getBufferCount() const = 0;
        virtual Buffer* getBuffer(const std::size_t index) = 0;
        virtual const Buffer* getBuffer(const std::size_t index) const = 0;
    };

    typedef std::unique_ptr<Mesh> MeshPtr;
}}

#endif 
