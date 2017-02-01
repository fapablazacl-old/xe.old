
#pragma once

#ifndef __xe_plugin_hpp__
#define __xe_plugin_hpp__

//#include <xe/RefCounted.hpp>
#include <xe/PluginData.hpp>

namespace xe {
    template<class Core>
    class Plugin /*: public RefCounted*/ {
    public:
        virtual ~Plugin() {}
        
        virtual PluginData getData() const = 0;

        virtual void start(Core *core) = 0;

        virtual void stop(Core *core) = 0;
    };

    template<typename Core>
    using XE_CreatePluginProc = Plugin<Core>* (*)(); 

#define XE_STR(value)                    #value
#define XE_GET_PLUGIN_OBJECT_NAME        XE_CreatePlugin
#define XE_GET_PLUGIN_OBJECT_NAME_STR    XE_STR(XE_CreatePlugin)

#define XE_EXPORT_PLUGIN(Core, PluginImpl) \
    extern "C" { \
        XE_API_EXPORT xe::Plugin<Core>* XE_CALLCONV XE_GET_PLUGIN_OBJECT_NAME() { \
            return new PluginImpl(); \
        } \
    }
}

#endif 
