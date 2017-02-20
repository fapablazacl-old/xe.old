
#pragma once

#ifndef __xe_gfx_inputmanager2glfw_hpp__
#define __xe_gfx_inputmanager2glfw_hpp__

#include <map>
#include <memory>
#include <xe/input/InputManager.hpp>
#include <xe/input/InputState.hpp>

#include "OpenGL.hpp"

namespace xe {

    class InputManagerGLFW : public InputManager {
    public:
        explicit InputManagerGLFW(GLFWwindow* window);

        virtual ~InputManagerGLFW();

        virtual InputStatus getStatus(const InputCode code) const override;

        virtual void poll() override;

    private:
        GLFWwindow *m_window = nullptr;
        std::map<int, InputCode> m_glfwToXE;
        std::map<InputCode, int> m_XEToglfw;
        InputState m_state;
    };
}

#endif 
