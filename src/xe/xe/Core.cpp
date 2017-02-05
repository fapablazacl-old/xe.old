/*
 * Copyright (c) 2016, 2017 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Core.hpp"

#include <cassert>
#include <xe/PluginManagerImpl.hpp>

namespace xe {

    struct Core::Private {
        GraphicsManager graphicsManager;
        PluginManagerImpl pluginManager;

        Version version = {XE_VERSION_MAJOR, XE_VERSION_MINOR};

        std::string license = "The XE Low Level Engine. \n"
            "Copyright (c) 2016, 2017 Felipe Apablaza\n\n"
            "The license and distribution terms for this library may be\n"
            "found in the file LICENSE in this distribution.\n";

        Private(Core *core) : pluginManager(core) {}
    };

    Core::Core() : m_impl(new Core::Private(this)) {
        std::cout << m_impl->license << std::endl;
    }

    Core::~Core() {
        delete m_impl;
    }

    Version Core::getVersion() const {
        assert(m_impl);

        return m_impl->version;
    }

    GraphicsManager* Core::getGraphicsManager() {
        assert(m_impl);

        return &m_impl->graphicsManager;
    }    

    PluginManager* Core::getPluginManager() {
        assert(m_impl);

        return &m_impl->pluginManager;
    }
}
