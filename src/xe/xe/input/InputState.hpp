
#pragma once 

#ifndef __xe_input_inputstate_hpp__
#define __xe_input_inputstate_hpp__

#include <xe/PreDef.hpp>

namespace xe {
    enum class InputStatus;
    enum class InputCode;

    class InputManager;

    class XE_API InputState {
    public:
        InputState();

        ~InputState();

        void fill(InputManager *manager);

        InputStatus getStatus(const InputCode code);

    private:
        struct Private;
        Private *m_impl;
    };
}

#endif
