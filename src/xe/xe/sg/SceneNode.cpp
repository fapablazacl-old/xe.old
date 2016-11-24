
#include "SceneNode.hpp"

namespace xe { namespace sg {

    class SceneNode;
    typedef std::unique_ptr<SceneNode> SceneNodePtr;
    
    struct SceneNode::Private {
    public:
        std::string m_name;
        Renderable *m_renderable = nullptr;
        Matrix4f m_matrix = Matrix4f::makeIdentity();
        
        std::vector<SceneNodePtr> m_childs;
        SceneNode *m_parent = nullptr;

    public:
        std::vector<SceneNodePtr>::iterator find(const SceneNode *node) {
            return std::find_if(m_childs.begin(), m_childs.end(), [node](SceneNodePtr &nodePtr) {
                return nodePtr.get() == node;
            });
        }
    };

    SceneNode::SceneNode() 
        : m_impl(new SceneNode::Private()) {}

    SceneNode::~SceneNode() {
        delete m_impl;
    }

    SceneNode* SceneNode::createNode() {
        assert(m_impl);

        auto* node = new SceneNode();

        m_impl->m_childs.emplace_back(node);

        return node;
    }
        
    void SceneNode::destroyNode(SceneNode *child) {
        assert(child);

        m_impl->m_childs.erase(this->m_impl->find(child));
    }

    SceneNode* SceneNode::SceneNode::setName(const std::string &name) {
        assert(m_impl);

        m_impl->m_name = name;
        return this;
    }

    SceneNode* SceneNode::setRenderable(Renderable *renderable) {
        assert(m_impl);

        m_impl->m_renderable = renderable;
        return this;
    }

    SceneNode* SceneNode::setMatrix(const Matrix4f &matrix) {
        assert(m_impl);

        m_impl->m_matrix = matrix;
        return this;
    }

    std::string SceneNode::getName() const {
        assert(m_impl);

        return m_impl->m_name;
    }

    Renderable* SceneNode::getRenderable() const {
        assert(m_impl);

        return m_impl->m_renderable;
    }

    Matrix4f SceneNode::getMatrix() const {
        assert(m_impl);

        return m_impl->m_matrix;
    }

    std::size_t SceneNode::getNodeCount() const {
        assert(m_impl);

        return m_impl->m_childs.size();
    }

    SceneNode* SceneNode::getNode(const std::size_t index) const {
        assert(m_impl);

        return m_impl->m_childs[index].get();
    }
}}
