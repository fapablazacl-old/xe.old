
#pragma once 

#ifndef __xe_sg_scenemanager_hpp__
#define __xe_sg_scenemanager_hpp__

#include <xe/PreDef.hpp>

namespace xe {
    class SceneNode;

    class XE_API SceneManager {
    public:
        virtual ~SceneManager();

        virtual void renderAll(const SceneNode *node) = 0;
    };
}

#endif 
