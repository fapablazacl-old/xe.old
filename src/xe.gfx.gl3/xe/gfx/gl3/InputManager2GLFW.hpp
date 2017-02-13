
#pragma once

#ifndef __xe_gfx_inputmanager2glfw_hpp__
#define __xe_gfx_inputmanager2glfw_hpp__

#include <map>
#include <memory>
#include <xe/input/InputManager2.hpp>

#include "OpenGL.hpp"

namespace xe {

    class InputManager2GLFW : public InputManager2 {
    public:
        explicit InputManager2GLFW(GLFWwindow* window);

        virtual ~InputManager2GLFW();

        virtual InputStatus getStatus(const InputCode code) override;

        virtual void poll() override;

    private:
        GLFWwindow *m_window = nullptr;
        std::map<int, InputCode> m_glfwToXE;
        std::map<InputCode, int> m_XEToglfw;
    };
}

#endif 
