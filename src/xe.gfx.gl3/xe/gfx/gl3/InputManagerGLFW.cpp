
#include "InputManagerGLFW.hpp"

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

    InputManagerGLFW::InputManagerGLFW(GLFWwindow* window) : m_window(window) {
        assert(window);

        for (const auto &pair : s_codemap) {
            m_glfwToXE.insert({pair.first, pair.second});
            m_XEToglfw.insert({pair.second, pair.first});
        }
    }

    InputManagerGLFW::~InputManagerGLFW() {}

    InputStatus InputManagerGLFW::getStatus(const InputCode code) const {
        assert(m_window);
        assert(code != InputCode::Last);

        return m_state.getStatus(code);
    }

    void InputManagerGLFW::poll() {
        assert(m_window);

        ::glfwPollEvents();

        for (int i=int(InputCode::First); i<int(InputCode::Last); i++) {
            const auto code = InputCode(i);

            const auto keyStatus = ::glfwGetKey(m_window, m_XEToglfw[code]);
            const auto status = s_status[keyStatus];

            m_state.setStatus(code, status);
        }
    }
}
