
#include "FileLocator.hpp"

#include <filesystem>

namespace xe {
    std::string FileLocator::locate(const std::string &name) {
        namespace fs = std::experimental::filesystem;

        std::string location = name;

        for (const std::string &path : m_paths) {
            location = path + name;

            if (fs::exists(fs::path(location))) {
                break;
            }
        }

        return location;
    }
}
