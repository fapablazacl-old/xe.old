
#pragma once 

#ifndef __xe_toolkit_renderable_hpp__
#define __xe_toolkit_renderable_hpp__

#include <xe/PreDef.hpp>

namespace xe { namespace ext {
    class XE_API Renderable {
    public:
        virtual ~Renderable();

        virtual void render() = 0;
    };
}}

#endif 
