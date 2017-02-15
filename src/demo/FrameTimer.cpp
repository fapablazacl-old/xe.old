
#include "FrameTimer.hpp"

#include <chrono>

namespace xe {
    typedef std::chrono::steady_clock clock;
    typedef decltype(clock::now()) time_point;
    typedef std::chrono::milliseconds milliseconds_t;

    struct FrameTimer::Private {
        time_point last = clock::now();
    };

    FrameTimer::FrameTimer() 
        : m_impl(new FrameTimer::Private()) {}

    FrameTimer::~FrameTimer() {}

    float FrameTimer::getSeconds() const {
        const auto diff = m_impl->last - clock::now();
        const auto milliseconds = std::chrono::duration_cast<milliseconds_t>(diff).count();
        const float seconds = static_cast<float>(milliseconds) / 1000.0f;

        m_impl->last = clock::now();

        return seconds;
    }
}
