
#ifdef __unix__

#include "Library.hpp"

#include <cassert>
#include <dlfcn.h>

namespace xe {
    
    struct Library::Private {
        std::string name;
        void *handle = nullptr;
    };

    Library::Library(const std::string &name) : m_impl(new Library::Private()) {
        assert(m_impl);

        m_impl->name = name;
        m_impl->handle = dlopen(name.c_str(), RTLD_LAZY);
        
        if (!m_impl->handle) {
            // TODO: notify error 
            // dlerror
        }
    }

    Library::~Library() {
        assert(m_impl);

        if (m_impl->handle) {
            dlclose(m_impl->handle);
            m_impl->handle = nullptr;
        }
        
        delete m_impl;
    }

    void* Library::getAddress(const std::string &proc) {
        assert(m_impl);
        return dlsym(m_impl->handle, proc.c_str());
    }
}

#endif
