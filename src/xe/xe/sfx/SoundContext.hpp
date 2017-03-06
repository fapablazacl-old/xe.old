
#pragma once

#ifndef __xe_sfx_soundcontext_hpp__
#define __xe_sfx_soundcontext_hpp__

#include <memory>
#include <xe/PreDef.hpp>

namespace xe {
    class Buffer;
    class BufferQueue;
    class Listener;
    class Source;
    
    class XE_API SoundContext {
    public:
        ~SoundContext();

        virtual std::unique_ptr<Listener> createListener() = 0;

        virtual std::unique_ptr<Source> createSource() = 0;

        virtual void setListener(const Listener *listener) = 0;

        virtual const Listener* getListener() const = 0;
    };
}

#endif
