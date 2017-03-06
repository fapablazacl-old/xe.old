
#pragma once

#ifndef __xe_sfx_sounddevice_hpp__
#define __xe_sfx_sounddevice_hpp__

#include <memory>
#include <xe/PreDef.hpp>

namespace xe {
    class Buffer;
    class BufferQueue;
    class SoundContext;
    
    class XE_API SoundDevice {
    public:
        ~SoundDevice();

        virtual std::unique_ptr<Buffer> createBuffer() = 0;

        virtual std::unique_ptr<BufferQueue> createBufferQueue() = 0;

        virtual std::unique_ptr<SoundContext> createContext() = 0;

        virtual void setContext(const SoundContext *context) = 0;

        virtual const SoundContext* getContext() const = 0;
    };
}

#endif
