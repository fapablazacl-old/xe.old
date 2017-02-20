
#pragma once 

#ifndef __xe_input_inputstatus_hpp__
#define __xe_input_inputstatus_hpp__

#include <xe/PreDef.hpp>
#include <string>

namespace xe {
    enum class InputStatus {
        Unknown = -1, 
        Release,
        Press, 
        Push, 
        Pop
    };

    std::string XE_API toString(const InputStatus status);
}

#endif
