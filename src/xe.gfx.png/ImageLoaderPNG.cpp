
#include "ImageLoaderPNG.hpp"

#include "lodepng/lodepng.h"

#include <map>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>

#include "ImagePNG.hpp"

namespace xe {
    class ImageProxyPNG : public ImageProxy {
    public:
        ImageProxyPNG(xe::Stream *stream) : m_stream(stream) {
            assert(stream);

            const std::uint32_t bufferLength = 512;

            std::uint32_t readed;
            std::uint8_t buffer[bufferLength];
        
            std::vector<std::uint8_t> imageBuffer;

            while( (readed = stream->read(buffer, bufferLength, 1)) > 0) {
                for (int i=0; i<int(readed); i++) {
                    imageBuffer.push_back(buffer[i]);
                }
            }

            m_error = lodepng::decode(m_pixels, m_width, m_height, imageBuffer);
        }

        virtual bool isValid() const override {
            return m_error != 0;
        }
        
        virtual std::string getErrorMessage() const override {
            return lodepng_error_text(m_error);
        }
        
        virtual ImagePtr getImage() const override {
            return std::make_unique<ImagePNG>(m_pixels, m_width, m_height);
        }

    private:
        xe::Stream *m_stream;
        std::string m_errorMessage;

        unsigned m_error;
        unsigned m_width, m_height;
        std::vector<std::uint8_t> m_pixels;
    };

    ImageLoaderPNG::ImageLoaderPNG() {}

    ImageLoaderPNG::~ImageLoaderPNG() {}

    ImageProxyPtr ImageLoaderPNG::createProxy(xe::Stream *stream) {
        assert(stream);
        return std::make_unique<ImageProxyPNG>(stream);
    }
}
