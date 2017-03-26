
#pragma once 

#ifndef __xe_sg_renderable_hpp__
#define __xe_sg_renderable_hpp__

#include <xe/PreDef.hpp>

namespace xe {
    /**
     * @brief A Renderable changes the multimedia state when it is rendered.
     */
    class XE_API Renderable {
    public:
        virtual ~Renderable();

        virtual void render() = 0;
    };
}

#endif 
