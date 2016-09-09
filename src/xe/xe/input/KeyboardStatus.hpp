
#pragma once 

#ifndef __xe_input_keyboardstatus__
#define __xe_input_keyboardstatus__

#include <array>
#include <algorithm>
#include <xe/PreDef.hpp>
#include <xe/input/KeyStatus.hpp>
#include <xe/input/KeyCode.hpp>

namespace xe { namespace input {
    class XE_API KeyboardStatus {
    public:
        KeyboardStatus();

        void setKeyStatus(KeyCode keyCode, KeyStatus keyStatus);

        KeyStatus getKeyStatus(KeyCode keyCode) const;

        bool isKeyPressed(KeyCode keyCode) const;
        bool isKeyReleased(KeyCode keyCode) const;
        bool isKeyPushed(KeyCode keyCode) const;
        bool isKeyPopped(KeyCode keyCode) const;

    private:
        static const int KEY_COUNT = static_cast<int>(KeyCode::Total) + 1;

        struct XE_API Status {
            std::array<KeyStatus, KEY_COUNT> status;

            Status() {
                std::generate(std::begin(status), std::end(status), []() {
                    return KeyStatus::Release;
                });
            }

            bool isPressed(KeyCode key) const {
                return status[static_cast<int>(key)] == KeyStatus::Press;
            }

            bool isReleased(KeyCode key) const {
                return status[static_cast<int>(key)] == KeyStatus::Release;
            }
        };

        Status m_current;
        Status m_previous;
    };
}}

#endif 
