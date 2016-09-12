
#include <xe/Core.hpp>

#include "PluginGL.hpp"

namespace xe { namespace gfx { namespace gl3 {
    static const char *s_pluginName = "OpenGL 3.3 Core Graphics Plugin";
    static const char *s_pluginDesc = "No description.";

    PluginGL::PluginGL() : m_factory({s_pluginName, s_pluginDesc, Driver::GL_core, Language::GLSL}) {}

    PluginGL::~PluginGL() {}

    std::string PluginGL::getName() const { 
        return s_pluginName;
    }

    std::string PluginGL::getDescription() const {
        return s_pluginDesc;
    }
           
    Version PluginGL::getVersion() const {
        return {1, 0, 0, 0};
    }

    void PluginGL::initialize(Core *core) { 
        m_core = core;
        m_core->getGraphicsManager()->registerFactory(&m_factory);
    }
           
    void PluginGL::terminate() {
        m_core->getGraphicsManager()->unregisterFactory(&m_factory);
    }
}}}

XE_EXPORT_PLUGIN(xe::gfx::gl3::PluginGL);
