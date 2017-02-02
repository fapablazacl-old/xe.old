
#include "Version.hpp"

#include <iostream>

namespace xe {
    XE_API bool operator== (const Version &v1, const Version &v2) {
        if (v1.major != v2.major) {
            return false;
        }

        if (v1.minor != v2.minor) {
            return false;
        }

        return true;
    }

    XE_API bool operator< (const Version &v1, const Version &v2) {
        if (v1.major >= v2.major) {
            return false;
        }

        if (v1.minor >= v2.minor) {
            return false;
        }

        return true;
    }

    XE_API std::ostream& operator<< (std::ostream &os, const Version &v) {
        os << v.major << "." << v.minor;

        return os;
    }
}
