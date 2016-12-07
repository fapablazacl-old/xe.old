
#pragma once

#ifndef __xe_sg_renderable_hpp__
#define __xe_sg_renderable_hpp__

#include <xe/PreDef.hpp>
#include <memory>
#include <xe/Box.hpp>
#include <xe/sg/Forward.hpp>

namespace xe { namespace sg {
    class XE_API Renderable {
    public:
        virtual ~Renderable();
        virtual void renderWith(xe::sg::Pipeline *renderer) = 0;
    };

    typedef std::unique_ptr<Renderable> RenderablePtr;
}}

#endif 
