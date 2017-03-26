
#pragma once 

#ifndef __xe_sg_sceneimpl_hpp__
#define __xe_sg_sceneimpl_hpp__

#include "Scene.hpp"

#include <memory>
#include <vector>

namespace xe {

    class SceneNodeImpl;

    class XE_API SceneImpl : public Scene {
    public:
        SceneImpl();

        virtual ~SceneImpl();

        virtual SceneNode* createNode() override;

        virtual SceneNode* createNode(SceneNode *parent) override;

    private:
        std::vector<std::unique_ptr<SceneNodeImpl>> m_nodes;
    };
}

#endif 
