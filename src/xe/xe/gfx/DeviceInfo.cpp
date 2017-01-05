
#include "DeviceInfo.hpp"

#include <ostream>

namespace xe {

    XE_API bool operator== (const GraphicsDeviceInfo &info1, const GraphicsDeviceInfo &info2) {
        if (info1.name != info2.name) {
            return false;
        }

        if (info1.desc != info2.desc) {
            return false;
        }

        if (info1.driver != info2.driver) {
            return false;
        }

        if (info1.lang != info2.lang) {
            return false;
        }

        return true;
    }

    XE_API bool operator< (const GraphicsDeviceInfo &info1, const GraphicsDeviceInfo &info2) {
        if (info1.name >= info2.name) {
            return false;
        }

        if (info1.desc >= info2.desc) {
            return false;
        }

        if (info1.driver >= info2.driver) {
            return false;
        }

        if (info1.lang >= info2.lang) {
            return false;
        }

        return true;
    }    
}

XE_API std::ostream& operator<< (std::ostream& os, const xe::GraphicsDeviceInfo &info) {
    os << "name: " << info.name << ", desc: "  << info.desc;

    return os;
}
