
#include <xe/Core.hpp>

#include "PluginGL.hpp"

namespace xe {
    static const char *s_pluginName = "OpenGL 3.3 Core Graphics Plugin";
    static const char *s_pluginDesc = "No description.";

    PluginGL::PluginGL() 
        : m_factory({s_pluginName, s_pluginDesc, Driver::GL_core, Language::GLSL}) {}

    PluginGL::~PluginGL() {}

    PluginData PluginGL::getData() const {
        return {s_pluginName, s_pluginDesc, {1, 0}};
    }

    void PluginGL::start(Core *core) {
        core->getGraphicsManager()->registerFactory(&m_factory);
    }

    void PluginGL::stop(Core *core) {
        core->getGraphicsManager()->unregisterFactory(&m_factory);
    }
}

#if defined(XE_PLUGIN_DYNAMIC_LINKING)
XE_EXPORT_PLUGIN(xe::Core, xe::PluginGL)
#endif
