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

namespace xe {
    class EXENGAPI Core;
}

namespace xe { namespace sys {
    class EXENGAPI Library;
    
    /**
     * @brief Plugin abstract class. All plugin-compliant modules must implement its methods
     */
    class EXENGAPI Plugin {
    public:
        virtual ~Plugin() = 0;
            
        /**
         * @brief Get the name of the plugin. The plugin name must be unique.
         */
        virtual std::string getName() const;

        /**
         * @brief Get the description of the plugin.
         */
        virtual std::string getDescription() const;
            
        /**
         * @brief Get the plugin version
         */
        virtual Version getVersion() const;

        /**
         * @brief Initializes the plugin, extending and implementing interfaces already present
         * in the specified root object.
         * @param root Root instance to extend.
         */
        virtual void initialize(Core *root);
            
        /**
         * @brief Terminate the plugin, removing its intefaces, and deallocating all created objects 
         * by any of its instances.
         */
        virtual void terminate();
    };
    
    typedef std::unique_ptr<Plugin> PluginPtr;

    /**
     * @brief Module level function signature. 
     *
     * All plugins must at least export a function with this signature.
     */
    typedef EXENG_EXPORT void (EXENG_CALLCONV *ExengGetPluginObjectProc)(std::unique_ptr<Plugin> &plugin); 
}}

/**
 * @brief The name of the function to export in the dynamic module.
 */
#define EXENG_STR(value)                    #value
#define EXENG_GET_PLUGIN_OBJECT_NAME        ExengGetPluginObject
#define EXENG_GET_PLUGIN_OBJECT_NAME_STR    EXENG_STR(ExengGetPluginObject)

/**
 * @brief Aids in implementing plugins.
 */
template<typename PluginClass>
void ExengGetPluginObjectImpl(std::unique_ptr<xe::sys::Plugin> &plugin) 
{
    plugin = std::unique_ptr<xe::sys::Plugin>(new PluginClass());
}

/**
 * @brief Export a plugin class on a DLL/SO
 */
#define EXENG_EXPORT_PLUGIN(PluginImpl)                                                                            \
extern "C" {                                                                                                    \
    EXENG_EXPORT void EXENG_CALLCONV ExengGetPluginObject(std::unique_ptr<xe::sys::Plugin> &plugin) {        \
        ExengGetPluginObjectImpl<PluginImpl>(plugin);                                                            \
    }                                                                                                            \
}

#endif //__EXENG_SYSTEM_PLUGIN_HPP__
