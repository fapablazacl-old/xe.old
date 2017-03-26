
#include "SceneImpl.hpp"
#include "SceneNodeImpl.hpp"

namespace xe {
    SceneImpl::SceneImpl() {}

    SceneImpl::~SceneImpl() {}

    SceneNode* SceneImpl::createNode() {
        return this->createNode(nullptr);
    }

    SceneNode* SceneImpl::createNode(SceneNode *parent) {
        auto node = new SceneNodeImpl(static_cast<SceneNodeImpl*>(parent));

        m_nodes.emplace_back(node);
        
        return node;
    }
}
