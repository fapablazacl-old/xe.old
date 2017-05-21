
#pragma once 

#ifndef __xe_sg_scenemanagerimpl_hpp__
#define __xe_sg_scenemanagerimpl_hpp__

#include "SceneManager.hpp"
#include "GenericSceneNode.hpp"
#include "Renderable.hpp"

#include <vector>
#include <cassert>

namespace xe {

    class Renderable;
    class GenericSceneManager : public SceneManager {
    public:
        GenericSceneManager() {}

        virtual ~GenericSceneManager() {}

        virtual void renderAll(const SceneNode *node) override {
            assert(node);

            std::vector<Renderable*> renderables;

            this->visit(renderables, static_cast<const GenericSceneNode*>(node));

            for (Renderable *renderable : renderables) {
                renderable->render();
            }
        }

    private:
        void visit(std::vector<Renderable*> &renderables, const GenericSceneNode *node) {
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
