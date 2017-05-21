
#pragma once 

#ifndef __xe_sg_scenenodeimpl_hpp__
#define __xe_sg_scenenodeimpl_hpp__

#include "SceneNode.hpp"
#include <vector>
#include <cassert>

namespace xe {
    class GenericSceneNode : public SceneNode {
    public:
        explicit GenericSceneNode() {}

        explicit GenericSceneNode(const std::string &name) {
            m_name = name;
        }

        virtual ~GenericSceneNode() {}

        virtual std::string getName() const override {
            return m_name;
        }

        virtual Renderable* getRenderable() const override {
            return m_renderable;
        }

        virtual GenericSceneNode* setRenderable(Renderable *renderable) override {
            m_renderable = renderable;

            return this;
        }

        virtual std::size_t getChildCount() const override {
            return m_childs.size();
        }

        virtual GenericSceneNode* getChild(const std::size_t index) const override {
            assert(index >= 0);
            assert(index < this->getChildCount());

            return m_childs[index];
        }

        virtual GenericSceneNode* getParent() const override {
            return m_parent;
        }

        virtual GenericSceneNode* setParent(SceneNode *parent) override {
            this->setParent(static_cast<GenericSceneNode*>(parent));

            return this;
        }

        void setParent(GenericSceneNode *parent) {
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
        GenericSceneNode *m_parent = nullptr;
        Renderable *m_renderable = nullptr;
        std::vector<GenericSceneNode*> m_childs;
    };
}

#endif 
