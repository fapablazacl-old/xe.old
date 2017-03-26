
#pragma once 

#ifndef __xe_sg_scenemanagerimpl_hpp__
#define __xe_sg_scenemanagerimpl_hpp__

#include "SceneManager.hpp"
#include "SceneNodeImpl.hpp"
#include "Renderable.hpp"

#include <vector>
#include <cassert>

namespace xe {

    class Renderable;
    class SceneNodeImpl;
    class SceneManagerImpl : public SceneManager {
    public:
        SceneManagerImpl() {}

        virtual ~SceneManagerImpl() {}

        virtual void renderAll(const SceneNode *node) override {
            assert(node);

            std::vector<Renderable*> renderables;

            this->visit(renderables, static_cast<const SceneNodeImpl*>(node));

            for (Renderable *renderable : renderables) {
                renderable->render();
            }
        }

    private:
        void visit(std::vector<Renderable*> &renderables, const SceneNodeImpl *node) {
            assert(node);

            if (node->getRenderable()) {
                renderables.push_back(node->getRenderable());
            }

            for (std::size_t i=0; i<node->getChildCount(); i++) {
                this->visit(renderables, node->getChild(i));
            }
        }
    };
}

#endif
