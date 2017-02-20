
#include "RenderSystem.hpp"

#include <xe/gfx/GraphicsDevice.hpp>
#include "render/Pipeline.hpp"
#include "render/SceneRenderer.hpp"

namespace demo {

    struct RenderSystem::Private {
        //xe::GraphicsDevice* m_device = nullptr;
        //xe::Pipeline *m_pipeline = nullptr;
        xe::SceneRenderer *m_sceneRenderer = nullptr;
        xe::Scene *m_scene = nullptr;
    };

    RenderSystem::RenderSystem(xe::Scene *scene, xe::SceneRenderer *sceneManager) : m_impl(new RenderSystem::Private()) {
        m_impl->m_scene = scene;
        m_impl->m_sceneRenderer = sceneManager;
    }

    RenderSystem::~RenderSystem() {}

    void RenderSystem::update()  {
        m_impl->m_sceneRenderer->renderFrame(m_impl->m_scene);
    }

    void RenderSystem::handle(AbstractMessage *message) {}
}
