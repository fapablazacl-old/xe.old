
#pragma once

#ifndef __xe_plugin_hpp__
#define __xe_plugin_hpp__

#include <xe/PreDef.hpp>
#include <xe/PluginData.hpp>

namespace xe {
    class XE_API Core;
    class XE_API Plugin {
    public:
        virtual ~Plugin();
        
        virtual PluginData getData() const = 0;

        virtual void start(Core *core) = 0;

        virtual void stop(Core *core) = 0;
    };

    typedef Plugin* (*XE_CreatePluginProc) ();

#define XE_STR(value)                    #value
#define XE_GET_PLUGIN_OBJECT_NAME        XE_CreatePlugin
#define XE_GET_PLUGIN_OBJECT_NAME_STR    XE_STR(XE_CreatePlugin)

#define XE_EXPORT_PLUGIN(Core, PluginImpl) \
    extern "C" { \
        XE_API_EXPORT xe::Plugin* XE_CALLCONV XE_GET_PLUGIN_OBJECT_NAME() { \
            return new PluginImpl(); \
        } \
    }
}

#endif 
