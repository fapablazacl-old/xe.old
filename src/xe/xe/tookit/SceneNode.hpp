
#pragma once 

#ifndef __xe_toolkit_scenenode_hpp__
#define __xe_toolkit_scenenode_hpp__

#include <xe/PreDef.hpp>

namespace xe { namespace ext {
    
    class Renderable;

    class XE_API SceneNode {
    public:
        virtual ~SceneNode();

        virtual Renderable* getRenderable() const = 0;

        virtual void setRenderable(Renderable *data) = 0;
    };
}}

#endif 
