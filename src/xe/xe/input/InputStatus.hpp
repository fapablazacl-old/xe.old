
#pragma once 

#ifndef __xe_input_inputstatus_hpp__
#define __xe_input_inputstatus_hpp__

namespace xe {
    enum class InputStatus {
        Unknown = -1, 
        Release,
        Press, 
        Push, 
        Pop
    };
}

#endif
