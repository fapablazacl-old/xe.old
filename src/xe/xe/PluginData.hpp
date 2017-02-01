
#pragma once

#ifndef __xe_plugindata_hpp__
#define __xe_plugindata_hpp__

#include <string>
#include <xe/Version.hpp>
#include <iosfwd>

namespace xe {
    struct PluginData {
        std::string name;
        std::string desc;
        Version version;

        PluginData() {}

        PluginData(std::string name_, std::string desc_, Version version_) 
            : name(name_), desc(desc_), version(version_) {}
    };
}

extern XE_API std::ostream& operator<< (std::ostream &os, const xe::PluginData &data);

#endif
