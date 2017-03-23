
#pragma once

#ifndef __xe_sg_scenenode__
#define __xe_sg_scenenode__

#include <vector>
#include <memory>

#include <xe/PreDef.hpp>
#include <xe/math/Matrix.hpp>
#include <xe/sg/Forward.hpp>

namespace xe {

    /**
     * @brief Node of some scene.
     */
    class XE_API SceneNode {
    public:
        SceneNode();

        ~SceneNode();

    public:
        /**
         * @brief Create and returns a new child node.
         */
        SceneNode* createNode(const std::string &name="");
        
        /** 
         * @brief Destroys the supplied child scene node only if a child of the current node.
         */
        void destroyNode(SceneNode *child);

        /**
         * @brief Set the name identifier of the node. Returns the 'this' pointer.
         */
        SceneNode* setName(const std::string &name) ;

        /**
         * @brief Set the associated renderable instance of the node. Returns the 'this' pointer.
         */
        SceneNode* setRenderable(Renderable *renderable);

        /**
         * @brief Set transformation matrix of the node. Returns the 'this' pointer.
         */
        SceneNode* setMatrix(const Matrix4f &matrix);

        /**
         * @brief Returns the current identifier name of the node.
         */
        std::string getName() const;

        /**
         * @brief Returns the associated renderable instance of the scene node.
         */
        Renderable* getRenderable() const;

        /**
         * @brief Returns the current transformation matrix.
         */
        Matrix4f getMatrix() const;

        /**
         * @brief Returns the total child count.
         */
        std::size_t getNodeCount() const ;

        /**
         * @brief Returns the node located at the specified index.
         */
        SceneNode* getNode(const std::size_t index) const;

        /**
         * @brief Get the node with the specified name
         */
        SceneNode* getNode(const std::string &name) const;

        /**
         * @brief Get the node located at the specified path.
         */
        SceneNode* findNode(const std::string &path) const;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
