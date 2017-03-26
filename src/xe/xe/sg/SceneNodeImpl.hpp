
#pragma once 

#ifndef __xe_sg_scenenodeimpl_hpp__
#define __xe_sg_scenenodeimpl_hpp__

#include "SceneNode.hpp"
#include <vector>

namespace xe {

    class XE_API SceneNodeImpl : public SceneNode {
    public:
        explicit SceneNodeImpl();

        explicit SceneNodeImpl(SceneNodeImpl *parent);

        virtual ~SceneNodeImpl();

        virtual Renderable* getRenderable() const override;

        virtual void setRenderable(Renderable *renderable) override;

        virtual std::size_t getChildCount() const override;

        virtual SceneNodeImpl* getChild(const std::size_t index) const override;

        virtual SceneNodeImpl* getParent() const override;

        virtual void setParent(SceneNode *parent) override;

        void setParent(SceneNodeImpl *parent);

    private:
        SceneNodeImpl *m_parent = nullptr;
        Renderable *m_renderable = nullptr;
        std::vector<SceneNodeImpl*> m_childs;
    };
}

#endif 
