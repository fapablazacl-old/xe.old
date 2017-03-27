
#pragma once

#ifndef __xe_archive_hpp__
#define __xe_archive_hpp__

#include <memory>
#include <string>
#include <set>
#include <xe/Stream.hpp>

namespace xe {
    class Stream;
    
    /**
     * @brief Opens various streams from a common source.
     *
     * By source, we mean a raw directory, a zipped folder, a base URL, etc.
     */
    class XE_API Archive {
    public:
        virtual ~Archive() {}

        /**
         * @brief Open a stream from the specified source (syntax depends on the archive), in read-only mode.
         */
        virtual std::unique_ptr<Stream> open(const std::string& name) = 0;

    public:
        /**
         * @brief Create a new Archive from the specified source.
         *
         * The only type of source supported for now is a physical directory.
         */
        static std::unique_ptr<Archive> create(const std::string &source);
    };
}

#endif
