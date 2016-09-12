/**
 * @file Plugin.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SYSTEM_PLUGIN_HPP__
#define __EXENG_SYSTEM_PLUGIN_HPP__

#include <memory>

#include <xe/Version.hpp>
#include <xe/Forward.hpp>
#include <xe/sys/Forward.hpp>

namespace xe { namespace sys {
    /**
     * @brief Plugin abstract class. All plugin-compliant modules must implement its methods
     */
    class XE_API Plugin {
    public:
        virtual ~Plugin();
            
        /**
         * @brief Get the name of the plugin. The plugin name must be unique.
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Get the description of the plugin.
         */
        virtual std::string getDescription() const = 0;
            
        /**
         * @brief Get the plugin version
         */
        virtual Version getVersion() const = 0;

        /**
         * @brief Initializes the plugin, extending and implementing interfaces already present
         * in the specified root object.
         * @param core Root instance to extend.
         */
        virtual void initialize(Core *core) = 0;
            
        /**
         * @brief Terminate the plugin, removing its intefaces, and deallocating all created objects 
         * by any of its instances.
         */
        virtual void terminate() = 0;
    };
    
    typedef std::unique_ptr<Plugin> PluginPtr;

    /**
     * @brief Module level function signature. 
     *
     * All plugins must at least export a function with this signature.
     */
    typedef XE_API_EXPORT void (XE_CALLCONV * ExengGetPluginObjectProc)(std::unique_ptr<Plugin> &plugin); 
}}

/**
 * @brief The name of the function to export in the dynamic module.
 */
#define XE_STR(value)                    #value
#define XE_GET_PLUGIN_OBJECT_NAME        XE_GetPluginObject
#define XE_GET_PLUGIN_OBJECT_NAME_STR    XE_STR(XE_GetPluginObject)

/**
 * @brief Aids in implementing plugins.
 */
template<typename PluginClass>
void XE_GetPluginObjectImpl(std::unique_ptr<xe::sys::Plugin> &plugin) {
    plugin = std::unique_ptr<xe::sys::Plugin>(new PluginClass());
}

/**
 * @brief Export a plugin class on a DLL/SO
 */
#define XE_EXPORT_PLUGIN(PluginImpl)                                                                \
extern "C" {                                                                                        \
    XE_API_EXPORT void XE_CALLCONV XE_GetPluginObject(std::unique_ptr<xe::sys::Plugin> &plugin) {   \
        XE_GetPluginObjectImpl<PluginImpl>(plugin);                                                 \
    }                                                                                               \
}

#endif //__EXENG_SYSTEM_PLUGIN_HPP__
