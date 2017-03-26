
#pragma once 

#ifndef __xe_frametimer_hpp__
#define __xe_frametimer_hpp__

#include <memory>

namespace xe {
    class FrameTimer {
    public:
        FrameTimer();

        ~FrameTimer();

        float getSeconds() const;

    private:
        struct Private;
        std::unique_ptr<Private> m_impl;
    };
}

#endif
