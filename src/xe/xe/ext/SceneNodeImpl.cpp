
#include "SceneNodeImpl.hpp"

#include <cassert>

namespace xe { namespace ext {
    SceneNodeImpl::SceneNodeImpl() {}

    SceneNodeImpl::SceneNodeImpl(SceneNodeImpl *parent) {
        this->setParent(parent);
    }

    SceneNodeImpl::~SceneNodeImpl() {}

    Renderable* SceneNodeImpl::getRenderable() const {
        return m_renderable;
    }

    void SceneNodeImpl::setRenderable(Renderable *renderable) {
        m_renderable = renderable;
    }

    std::size_t SceneNodeImpl::getChildCount() const {
        return m_childs.size();
    }

    SceneNodeImpl* SceneNodeImpl::getChild(const std::size_t index) const {
        assert(index >= 0);
        assert(index < this->getChildCount());

        return m_childs[index];
    }

    SceneNodeImpl* SceneNodeImpl::getParent() const {
        return m_parent;
    }

    void SceneNodeImpl::setParent(SceneNode *parent) {
        this->setParent(static_cast<SceneNodeImpl*>(parent));
    }

    void SceneNodeImpl::setParent(SceneNodeImpl* parent) {
        if (m_parent == parent) {
            return;
        }

        if (m_parent) {
            auto &childs = m_parent->m_childs;
            auto where = std::find(childs.begin(), childs.end(), this);

            assert(where != childs.end());
            childs.erase(where);
        }

        m_parent = parent;

        if (m_parent) {
            m_parent->m_childs.push_back(this);
        }
    }
}}
