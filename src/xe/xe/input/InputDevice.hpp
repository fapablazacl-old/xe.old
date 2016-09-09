
#pragma once 

#ifndef __xe_input_inputdevice__
#define __xe_input_inputdevice__

#include <xe/PreDef.hpp>

namespace xe { namespace input {
    class XE_API InputDevice {
    public:
        virtual ~InputDevice() {}
        virtual void poll() = 0;
    };
}}

#endif 
