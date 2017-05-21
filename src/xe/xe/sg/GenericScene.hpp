
#pragma once 

#ifndef __xe_sg_sceneimpl_hpp__
#define __xe_sg_sceneimpl_hpp__

#include "Scene.hpp"
#include "GenericSceneNode.hpp"

#include <memory>
#include <vector>

namespace xe {
    class GenericScene : public Scene {
    public:
        GenericScene() {
            m_root = this->createNode();
        }

        virtual ~GenericScene() {}

        virtual GenericSceneNode* getRoot() override {
            return m_root;
        }

        virtual GenericSceneNode* createNode() override {
            return this->createNode("", m_root);
        }

        virtual GenericSceneNode* createNode(const std::string &name) override {
            auto node = new GenericSceneNode(name);

            node->setParent(m_root);

            m_nodes.emplace_back(node);
        
            return node;
        }

        virtual GenericSceneNode* createNode(const std::string &name, SceneNode *parent) override {
            auto node = new GenericSceneNode(name);

            node->setParent(parent);

            m_nodes.emplace_back(node);
        
            return node;
        }

    private:
        std::vector<std::unique_ptr<GenericSceneNode>> m_nodes;
        GenericSceneNode *m_root = nullptr;
    };
}

#endif 
