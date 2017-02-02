
#pragma once

#ifndef __xe_corebase_hpp__
#define __xe_corebase_hpp__

#include <memory>

#include <xe/PluginManager.hpp>
#include <xe/PluginManagerImpl.hpp>

namespace xe { 

    template<class Core, class PluginManagerImpl_=xe::PluginManagerImpl<Core>>
    class CoreBase {
    public:
        CoreBase() : m_pluginManager(static_cast<Core*>(this)) {}

        virtual ~CoreBase() {}

        PluginManager<Core>* getPluginManager() {
            return &m_pluginManager;
        }

    private:
        PluginManagerImpl_ m_pluginManager;
    };
}

#endif 
