
#include "Archive.hpp"
#include "FileStream.hpp"

namespace xe {

    /**
     * @brief Simple stream instancer for files in a Directory.
     */
    class DirectoryArchive : public Archive {
    public:
        explicit DirectoryArchive(const std::string &base = "") : m_base(base) {
            auto isSeparator = [](const char ch) {
                return ch=='/' || ch=='\\';
            };

            if (isSeparator(base[base.size() - 1])) {
                m_base += "/";
            }
        }

        virtual ~DirectoryArchive() {}

        virtual std::unique_ptr<Stream> open(const std::string& name) override {
            return std::make_unique<FileStream>(m_base + name);
        }

    private:
        std::string m_base;
    };

    std::unique_ptr<Archive> Archive::create(const std::string &source) {
        return std::make_unique<DirectoryArchive>(source);
    }
}
