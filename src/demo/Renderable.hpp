
#pragma once

#ifndef __xe_sg_renderable_hpp__
#define __xe_sg_renderable_hpp__

#include <memory>
#include <typeindex>

namespace xe {
    class Renderable {
    public:
        virtual ~Renderable();

        virtual std::type_index getTypeIndex() const = 0;
    };

    typedef std::unique_ptr<Renderable> RenderablePtr;
}

#endif 
