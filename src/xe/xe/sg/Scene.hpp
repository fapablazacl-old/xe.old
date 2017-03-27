
#pragma once 

#ifndef __xe_sg_scene_hpp__
#define __xe_sg_scene_hpp__

#include <xe/PreDef.hpp>
#include <memory>
#include <string>

namespace xe {
    class SceneNode;
    
    /**
     * @brief 
     */
    class XE_API Scene {
    public:
        virtual ~Scene();

        virtual SceneNode* getRoot() = 0;

        virtual SceneNode* createNode() = 0;
        virtual SceneNode* createNode(const std::string &name) = 0;
        virtual SceneNode* createNode(const std::string &name, SceneNode *parent) = 0;
    };
}

#endif
