
#ifdef _WIN32

#include "Library.hpp"

#include <iostream>
#include <cassert>
#include <Windows.h>

namespace xe {
    struct Library::Private {
        std::string name;
        HMODULE hModule = nullptr;
    };

    Library::Library(const std::string &name) : m_impl(new Library::Private()) {
        assert(m_impl);

        m_impl->name = name;        
        m_impl->hModule = ::LoadLibrary(name.c_str());

        if (!m_impl->hModule) {
            const std::string msg = "xe::Library::Library: Couldn't load library '" + name + "'";

            std::clog << msg << std::endl;

            throw std::runtime_error(msg);
        }
    }

    Library::~Library() {
        assert(m_impl);

        if (m_impl->hModule) {
            ::FreeLibrary(m_impl->hModule);
        }

        delete m_impl;
    }

    void* Library::getAddress(const std::string &procedureName) {
        assert(m_impl);

        return ::GetProcAddress(m_impl->hModule, procedureName.c_str());
    }
}

#endif
