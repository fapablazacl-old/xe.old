
#include "PluginGLES2.hpp"

#include <cassert>
#include <GLFW/glfw3.h>

namespace xe { namespace gfx {
    PluginGLES2::PluginGLES2() {}

    PluginGLES2::~PluginGLES2() {}

    PluginData PluginGLES2::getData() const {
        PluginData data;

        data.name = "OpenGL ES Plugin";
        data.version = {1, 0};

        return data;
    }

    void PluginGLES2::start(Core *core) {
        assert(core);

        ::glfwInit();
        core->getGraphicsManager()->registerFactory(&m_factory);
    }

    void PluginGLES2::stop(Core *core)  {
        assert(core);

        core->getGraphicsManager()->unregisterFactory(&m_factory);
        ::glfwTerminate();
    }
}}

XE_EXPORT_PLUGIN(xe::Core, xe::gfx::PluginGLES2)
