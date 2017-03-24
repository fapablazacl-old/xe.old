
#include "SceneManagerImpl.hpp"
#include "Renderable.hpp"
#include "SceneNodeImpl.hpp"
#include <cassert>

namespace xe { namespace ext {

    SceneManagerImpl::SceneManagerImpl() {}

    SceneManagerImpl::~SceneManagerImpl() {}

    void SceneManagerImpl::renderAll(const SceneNode *node) {
        assert(node);

        std::vector<Renderable*> renderables;

        this->visit(renderables, static_cast<const SceneNodeImpl*>(node));

        for (Renderable *renderable : renderables) {
            renderable->render();
        }
    }

    void SceneManagerImpl::visit(std::vector<Renderable*> &renderables, const SceneNodeImpl *node) {
        assert(node);

        if (node->getRenderable()) {
            renderables.push_back(node->getRenderable());
        }

        for (std::size_t i=0; i<node->getChildCount(); i++) {
            this->visit(renderables, node->getChild(i));
        }
    }
}}
