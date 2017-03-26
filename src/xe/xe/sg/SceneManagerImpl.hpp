
#pragma once 

#ifndef __xe_sg_scenemanagerimpl_hpp__
#define __xe_sg_scenemanagerimpl_hpp__

#include "SceneManager.hpp"
#include <vector>

namespace xe {

    class Renderable;
    class SceneNodeImpl;
    class XE_API SceneManagerImpl : public SceneManager {
    public:
        SceneManagerImpl();

        virtual ~SceneManagerImpl();

        virtual void renderAll(const SceneNode *node) override;

    private:
        void visit(std::vector<Renderable*> &renderables, const SceneNodeImpl *node);
    };
}

#endif
