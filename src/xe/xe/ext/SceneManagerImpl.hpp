
#pragma once 

#ifndef __xe_toolkit_scenemanagerimpl_hpp__
#define __xe_toolkit_scenemanagerimpl_hpp__

#include "SceneManager.hpp"
#include <vector>

namespace xe { namespace ext {

    class Renderable;
    class SceneNodeImpl;
    class SceneManagerImpl : public SceneManager {
    public:
        SceneManagerImpl();

        virtual ~SceneManagerImpl();

        virtual void renderAll(const SceneNode *node) override;

    private:
        void visit(std::vector<Renderable*> &renderables, const SceneNodeImpl *node);
    };
}}

#endif
