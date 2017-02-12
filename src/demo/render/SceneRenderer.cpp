
#include "SceneRenderer.hpp"

#include <cstring>
#include <vector>

namespace xe {

    struct RenderElement {
        xe::Matrix4f transformation;
        xe::Renderable *renderable = nullptr;

        RenderElement(const xe::Matrix4f &transformation_, xe::Renderable *renderable_) 
            : transformation(transformation_), renderable(renderable_) {

            assert(renderable);
        }
    };

    struct SceneRenderer::Private {
        xe::Pipeline *pipeline = nullptr;

        void filterNode(std::vector<RenderElement> &elements, const xe::Matrix4f &parentTransformation, const xe::SceneNode *node) {
            assert(node);

            xe::Matrix4f transformation = parentTransformation * node->getMatrix();
            xe::Renderable *renderable = node->getRenderable();

            if (renderable) {
                elements.push_back({transformation, renderable});
            }

            for (std::size_t i=0; i<node->getNodeCount(); i++) {
                this->filterNode(elements, transformation, node->getNode(i));
            }
        }

        std::vector<RenderElement> filterScene(const xe::Scene *scene) {
            assert(scene);

            std::vector<RenderElement> elements;

            this->filterNode(elements, xe::Matrix4f::makeIdentity(), scene->getRootNode());

            return elements;
        }
    };

    SceneRenderer::SceneRenderer(xe::Pipeline *pipeline)
        : m_impl(new SceneRenderer::Private()) {

        assert(pipeline);

        m_impl->pipeline = pipeline;
    }
    
    SceneRenderer::~SceneRenderer() {
        delete m_impl;
    }

    void SceneRenderer::renderFrame(const xe::Scene *scene) {
        assert(m_impl);
        assert(scene);

        // extract render data
        const xe::Vector4f backColor = scene->getBackColor();

        const std::vector<RenderElement> elements = m_impl->filterScene(scene);

        xe::Pipeline *pipeline = m_impl->pipeline;
        assert(pipeline);

        // render the full scene
        pipeline->beginFrame();

        for (const RenderElement &element : elements) {
            pipeline->setTransform(TransformType::Model, element.transformation);
            pipeline->render(element.renderable);
        }

        pipeline->endFrame();
    }
}
