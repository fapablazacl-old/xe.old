
#include "InputManager2GLFW.hpp"

#include <cassert>
#include <map>
#include <xe/input/InputCode.hpp>
#include <xe/input/InputStatus.hpp>

namespace xe {

    static const std::pair<int, InputCode> s_codemap[] = {
        {GLFW_KEY_ESCAPE    , InputCode::KeyEsc},
        {GLFW_KEY_LEFT      , InputCode::KeyLeft},
        {GLFW_KEY_RIGHT     , InputCode::KeyRight},
        {GLFW_KEY_UP        , InputCode::KeyUp},
        {GLFW_KEY_DOWN      , InputCode::KeyDown},
        {GLFW_KEY_ENTER     , InputCode::KeyEnter}, 
        {GLFW_KEY_SPACE     , InputCode::KeySpace}
    };

    static InputStatus s_status[] = {
        InputStatus::Release,
        InputStatus::Press
    };

    InputManager2GLFW::InputManager2GLFW(GLFWwindow* window) : m_window(window) {
        assert(window);

        for (const auto &pair : s_codemap) {
            m_glfwToXE.insert({pair.first, pair.second});
            m_XEToglfw.insert({pair.second, pair.first});
        }
    }

    InputManager2GLFW::~InputManager2GLFW() {}

    InputStatus InputManager2GLFW::getStatus(const InputCode code) {
        assert(m_window);

        int inputStatus = ::glfwGetKey(m_window, m_XEToglfw[code]);

        return s_status[inputStatus];
    }

    void InputManager2GLFW::poll() {
        ::glfwPollEvents();
    }
}
