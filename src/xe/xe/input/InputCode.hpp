
#pragma once 

#ifndef __xe_input_inputcode_hpp__
#define __xe_input_inputcode_hpp__

#include <xe/PreDef.hpp>
#include <string>

namespace xe {
    enum class InputCode {
        Unknown,
        First, 
        KeyEsc = First,
        KeyEnter,
        KeyUp,
        KeyDown,
        KeyLeft,
        KeyRight,
        KeySpace,
        KeyLControl,
        KeyRControl,
        KeyLShift,
        KeyRShift,
        KeyTab,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        Key0,

        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,

        KeyQ,
        KeyW,
        KeyE,
        KeyR,
        KeyT,
        KeyY,
        KeyU,
        KeyI,
        KeyO,
        KeyP,

        KeyA,
        KeyS,
        KeyD,
        KeyF,
        KeyG,
        KeyH,
        KeyJ,
        KeyK,
        KeyL,

        KeyZ,
        KeyX,
        KeyC,
        KeyV,
        KeyB,
        KeyN,
        KeyM, 

        ButtonLeft,
        ButtonRight,
        ButtonMiddle,

        Last
    };

    std::string XE_API toString(const InputCode code);
}

#endif
