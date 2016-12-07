
#pragma once

#ifndef __xe_sg_scenerenderer_hpp__
#define __xe_sg_scenerenderer_hpp__

#include <xe/sg/Scene.hpp>

#include "Pipeline.hpp"

namespace xe { namespace sg {
    class SceneRenderer {
    public:
        explicit SceneRenderer(xe::sg::Pipeline *pipeline);

        ~SceneRenderer();

        void renderFrame(const xe::sg::Scene *scene);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}}

#endif
