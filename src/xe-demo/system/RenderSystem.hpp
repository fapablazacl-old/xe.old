
#pragma once

#ifndef __demo_rendersystem_hpp__
#define __demo_rendersystem_hpp__

#include "System.hpp"

#include <memory>

namespace xe {
    class Scene;
    class SceneRenderer;
}

namespace demo {
    class RenderSystem : public System {
    public:
        RenderSystem(xe::Scene *scene, xe::SceneRenderer *sceneManager);

        virtual ~RenderSystem();

        virtual void update() override;

        virtual void handle(AbstractMessage *message) override;

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
