
#pragma once 

#ifndef __xe_input_keystatus__
#define __xe_input_keystatus__

namespace xe {
    enum class KeyStatus {
        Release,
        Press,
        Unknown
    };

    inline bool isPressed(KeyStatus status) {
        return status==KeyStatus::Press;
    }

    inline bool isReleased(KeyStatus status) {
        return status==KeyStatus::Release;
    }
}

#endif
