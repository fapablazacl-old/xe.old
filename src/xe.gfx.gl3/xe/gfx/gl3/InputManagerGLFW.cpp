

#include "InputManagerGLFW.hpp"
#include "DeviceGL.hpp"

#include <map>

namespace xe {

    static std::map<int, xe::KeyCode> keymaps = {
        {GLFW_KEY_ESCAPE    , xe::KeyCode::KeyEsc},
        {GLFW_KEY_LEFT      , xe::KeyCode::KeyLeft},
        {GLFW_KEY_RIGHT     , xe::KeyCode::KeyRight},
        {GLFW_KEY_UP        , xe::KeyCode::KeyUp},
        {GLFW_KEY_DOWN      , xe::KeyCode::KeyDown},
        {GLFW_KEY_ENTER     , xe::KeyCode::KeyEnter}, 
        {GLFW_KEY_SPACE     , xe::KeyCode::KeySpace}
    };

    static xe::KeyStatus s_status[] = {
        xe::KeyStatus::Release,
        xe::KeyStatus::Press
    };

    void KeyboardGLFW::poll() {
        if (!window) {
            return;
        }

        for (const auto &pair : keymaps) {
            auto keyStatus = s_status[::glfwGetKey(window, pair.first)];
            
            status.setKeyStatus(pair.second, keyStatus);
        }
    }

    void xe_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT) {
            return;
        }
        
        //auto driver = static_cast<xe::GraphicsDeviceGLDeviceGL*>(::glfwGetWindowUserPointer(window));
        //auto manager = static_cast<InputManagerGLFW*>(driver->getInputManager());

        //// determine key code
        //auto code = xe::KeyCode::Unknown;

        //auto keyIterator = keymaps.find(key);
        //if (keyIterator != keymaps.end()) {
        //    code = keyIterator->second;
        //}

        //if (code == xe::KeyCode::Unknown) {
        //    return;
        //}

        //// determine key status
        //auto status = s_status[action];
        //
        //// set the key status
        //manager->getKeyboard()->getStatus()->setKeyStatus(code, status);
    }

    InputManagerGLFW::InputManagerGLFW() {}

    InputManagerGLFW::InputManagerGLFW(GLFWwindow* window) {
        this->setWindow(window);
    }

    void InputManagerGLFW::poll() {
        ::glfwPollEvents();

        m_keyboard.poll();
    }

    void InputManagerGLFW::setWindow(GLFWwindow *window) {
        ::glfwSetKeyCallback(window, xe_handle_key);

        m_window = window;
        m_keyboard.window = window;
    }
}
