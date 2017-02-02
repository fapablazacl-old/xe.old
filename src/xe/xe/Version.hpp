
#pragma once

#ifndef __xe_version_hpp__
#define __xe_version_hpp__

#include <xe/PreDef.hpp>
#include <iosfwd>

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif

namespace xe {
    struct Version {
        int major = 0;
        int minor = 0;

        Version() {}
        Version(int major_, int minor_) : major(major_), minor(minor_) {}
    };

    extern XE_API bool operator== (const Version &v1, const Version &v2);

    extern XE_API bool operator< (const Version &v1, const Version &v2);

    extern XE_API std::ostream& operator<< (std::ostream &os, const Version &v);

    inline bool operator!= (const Version &v1, const Version &v2) {
        return !(v1 == v2);
    }

    inline bool operator>= (const Version &v1, const Version &v2) {
        return !(v1 < v2);
    }

    inline bool operator<= (const Version &v1, const Version &v2) {
        return (v1 < v2) || (v1 == v2);
    }

    inline bool operator> (const Version &v1, const Version &v2) {
        return !(v1 <= v2);
    }
}

#endif
