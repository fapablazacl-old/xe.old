
#include "PluginData.hpp"

#include <ostream>

XE_API std::ostream& operator<< (std::ostream &os, const xe::PluginData &data) {
    os << "name: " << data.name << ", description: " << data.desc << ", version: " << data.version;

    return os;
}
