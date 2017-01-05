
#pragma once

#ifndef __xe_gfx_inputmanagerglfw_hpp__
#define __xe_gfx_inputmanagerglfw_hpp__

#include <memory>
#include <xe/input/InputManager.hpp>
#include <xe/input/EventImpl.hpp>
#include "OpenGL.hpp"

namespace xe {

    class KeyboardGLFW : public Keyboard {
    public:
        KeyboardGLFW() {}

        virtual ~KeyboardGLFW() {}

        virtual KeyboardStatus* getStatus() override {
            return &status;
        }

        virtual const KeyboardStatus* getStatus() const override {
            return &status;
        }

        virtual Event<KeyStroke>* getKeyStrokeEvent() override {
            return &keyStrokeEvent;
        }

        virtual void poll() override;

        KeyboardStatus status;
        EventImpl<KeyStroke> keyStrokeEvent;
        GLFWwindow *window = nullptr;
    };

    class MouseGLFW : public Mouse {
    public:
        virtual MouseStatus getStatus() override {
            return status;
        }

        virtual void poll() override {}

        MouseStatus status;
    };

    class InputManagerGLFW : public InputManager {
    public:
        InputManagerGLFW();
        explicit InputManagerGLFW(GLFWwindow* window);

        virtual ~InputManagerGLFW() {}

        virtual KeyboardGLFW* getKeyboard() override {
            return &m_keyboard;
        }

        virtual MouseGLFW* getMouse() override {
            return &m_mouse;
        }

        void setWindow(GLFWwindow *window);

        GLFWwindow* getWindow() {
            return this->m_window;
        }

        const GLFWwindow* getWindow() const {
            return this->m_window;
        }

        virtual void poll() override;

    private:
        GLFWwindow *m_window = nullptr;
        KeyboardGLFW m_keyboard;
        MouseGLFW m_mouse;
    };
}

#endif 
