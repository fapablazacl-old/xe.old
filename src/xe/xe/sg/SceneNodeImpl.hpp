
#pragma once 

#ifndef __xe_sg_scenenodeimpl_hpp__
#define __xe_sg_scenenodeimpl_hpp__

#include "SceneNode.hpp"
#include <vector>
#include <cassert>

namespace xe {
    class SceneNodeImpl : public SceneNode {
    public:
        explicit SceneNodeImpl() {}

        explicit SceneNodeImpl(const std::string &name) {
            m_name = name;
        }

        virtual ~SceneNodeImpl() {}

        virtual std::string getName() const override {
            return m_name;
        }

        virtual Renderable* getRenderable() const override {
            return m_renderable;
        }

        virtual SceneNodeImpl* setRenderable(Renderable *renderable) override {
            m_renderable = renderable;

            return this;
        }

        virtual std::size_t getChildCount() const override {
            return m_childs.size();
        }

        virtual SceneNodeImpl* getChild(const std::size_t index) const override {
            assert(index >= 0);
            assert(index < this->getChildCount());

            return m_childs[index];
        }

        virtual SceneNodeImpl* getParent() const override {
            return m_parent;
        }

        virtual SceneNodeImpl* setParent(SceneNode *parent) override {
            this->setParent(static_cast<SceneNodeImpl*>(parent));

            return this;
        }

        void setParent(SceneNodeImpl *parent) {
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

    private:
        std::string m_name;
        SceneNodeImpl *m_parent = nullptr;
        Renderable *m_renderable = nullptr;
        std::vector<SceneNodeImpl*> m_childs;
    };
}

#endif 
