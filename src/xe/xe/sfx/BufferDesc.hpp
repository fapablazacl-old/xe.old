
#pragma once

#ifndef __xe_sfx_bufferdesc_hpp__
#define __xe_sfx_bufferdesc_hpp__

#include <cstdint>

namespace xe {
    struct BufferDesc {
        std::uint32_t size;
        std::uint16_t frequency;
        std::uint8_t bits;
        std::uint8_t channels;
    };
}

#endif
