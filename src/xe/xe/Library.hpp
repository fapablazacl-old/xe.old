
#pragma once

#ifndef __xe_library_hpp__
#define __xe_library_hpp__

#include <string>
#include <xe/PreDef.hpp>

namespace xe {
    class XE_API Library {
    public:
        Library(const std::string &name);

        ~Library();

        void* getAddress(const std::string &procedureName);

    private:
        Library(const Library&) = delete;
        void operator=(const Library&) = delete;

    private:
        struct Private;
        Private* m_impl;
    };
}

#endif
