
#include "InputState.hpp"

#include <map>
#include <cassert>

#include "InputCode.hpp"
#include "InputStatus.hpp"

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

    void InputState::setStatus(const InputCode code, const InputStatus status) {
        assert(m_impl);
        assert(code != InputCode::Unknown);
        assert(code != InputCode::Last);
        assert(status == InputStatus::Release || status == InputStatus::Press);

        m_impl->m_previous[code] = m_impl->m_current[code];
        m_impl->m_current[code] = status;
    }

    InputStatus InputState::getStatus(const InputCode code) const {
        assert(code != InputCode::Unknown);
        assert(code != InputCode::Last);

        InputStatus status = InputStatus::Unknown;

        const auto current = m_impl->m_current[code];
        const auto previous = m_impl->m_previous[code];

        if (current == previous) {
            return current;
        }

        if (previous == InputStatus::Press && current == InputStatus::Release) {
            status = InputStatus::Pop;

        } else if (previous == InputStatus::Release && current == InputStatus::Press) {
            status = InputStatus::Push;
        }

        return status;
    }
}
