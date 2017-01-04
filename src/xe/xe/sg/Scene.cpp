
#include "Scene.hpp"

namespace xe {

    struct Scene::Private {
        Vector4f backcolor = {0.2f, 0.2f, 0.2f, 1.0f};
        SceneNode rootNode;
    };

    Scene::Scene() : m_impl(new Scene::Private()) {}

    const SceneNode* Scene::getNode() const {
        assert(m_impl);
        return &m_impl->rootNode;
    }

    SceneNode* Scene::getNode() {
        assert(m_impl);
        return &m_impl->rootNode;
    }

    Vector4f Scene::getBackColor() const {
        return m_impl->backcolor;
    }

    Scene* Scene::setBackColor(const Vector4f &color) {
        assert(m_impl);
        m_impl->backcolor = color;

        return this;
    }

    Scene::~Scene() {
        delete m_impl;
    }
}
