
#pragma once 

#ifndef __xe_toolkit_scenemanager_hpp__
#define __xe_toolkit_scenemanager_hpp__

#include <xe/PreDef.hpp>

namespace xe { namespace ext {

    class SceneNode;

    class XE_API SceneManager {
    public:
        virtual ~SceneManager();

        virtual void renderAll(const SceneNode *node) = 0;
    };
}}

#endif 
