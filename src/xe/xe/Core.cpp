/**
 * @file
 * @brief Root class implementation
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Core.hpp"

namespace xe {
    static const char licenseMsg[] = 
        "The XE C++ engine. \n"
        "Copyright (c) 2016 Felipe Apablaza\n\n"
        "The license and distribution terms for this library may be\n"
        "found in the file LICENSE in this distribution.\n";
    
    Core::Core() {
        m_pluginManager.setCore(this);

        std::cout << licenseMsg << std::endl;
    }

    Core::~Core() {}

    Version Core::getVersion() const {
        return {XE_VERSION_MAJOR, XE_VERSION_MINOR, XE_VERSION_REVISION, XE_VERSION_BUILD};
    }
}
