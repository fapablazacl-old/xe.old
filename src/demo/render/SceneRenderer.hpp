
#pragma once

#ifndef __xe_sg_scenerenderer_hpp__
#define __xe_sg_scenerenderer_hpp__

#include <xe/sg/Scene.hpp>

#include "Pipeline.hpp"

namespace xe {
    class SceneRenderer {
    public:
        explicit SceneRenderer(Pipeline *pipeline);

        ~SceneRenderer();

        void renderFrame(const Scene *scene);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
