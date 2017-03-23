
#pragma once 

#ifndef __xe_toolkit_scene_hpp__
#define __xe_toolkit_scene_hpp__

#include <xe/PreDef.hpp>

namespace xe { namespace ext {  //! Extension namespace

    class SceneNode;
    
    /**
     * @brief 
     */
    class XE_API Scene {
    public:
        virtual ~Scene();

        virtual SceneNode* createNode() = 0;
        virtual SceneNode* createNode(SceneNode *parent) = 0;
    };
}}

#endif
