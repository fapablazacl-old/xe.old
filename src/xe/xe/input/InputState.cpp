
#include "InputState.hpp"

#include "InputManager2.hpp"
#include "InputCode.hpp"
#include "InputStatus.hpp"

#include <map>
#include <cassert>

namespace xe {

    struct InputState::Private {
        std::map<InputCode, InputStatus> m_current;
        std::map<InputCode, InputStatus> m_previous;
    };

    InputState::InputState() 
        : m_impl(new InputState::Private()) {}

    InputState::~InputState() {
        delete m_impl;
    }

    void InputState::fill(InputManager2 *manager) {
        assert(m_impl);
        assert(manager);

        for (int i=int(InputCode::First); i<int(InputCode::Last); i++) {
            const auto code = InputCode(i);

            // update previous and current elemental status
            m_impl->m_previous[code] = m_impl->m_current[code];
            m_impl->m_current[code] = manager->getStatus(code);
        }
    }

    InputStatus InputState::getStatus(const InputCode code) {
        assert(code != InputCode::Unknown);
        assert(code != InputCode::Last);

        const auto current = m_impl->m_current[code];
        const auto previous = m_impl->m_previous[code];

        if (current == previous) {
            return current;
        }

        if (previous == InputStatus::Press && current == InputStatus::Release) {
            return InputStatus::Pop;
        }

        if (previous == InputStatus::Release && current == InputStatus::Press) {
            return InputStatus::Push;
        }
    }
}
