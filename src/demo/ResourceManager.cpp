
#include "ResourceManager.hpp"

#include <xe/FileStream.hpp>

namespace xe {
    class FileArchive : public Archive {
    public:
        explicit FileArchive(const std::string &base = "") : m_base(base) {
            auto isSeparator = [](const char ch) {
                return ch=='/' || ch=='\\';
            };

            if (isSeparator(base[base.size() - 1])) {
                m_base += "/";
            }
        }

        virtual ~FileArchive() {}

        virtual std::unique_ptr<Stream> open(const std::string& name) override {
            return std::make_unique<FileStream>(m_base + name);
        }

    private:
        std::string m_base;
    };

    std::unique_ptr<Archive> Archive::create(const std::string &source) {
        // TODO: For now, just construct a FileArchive instance
        return std::make_unique<FileArchive>(source);
    }
}
