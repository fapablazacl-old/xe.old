
#include "InputStatus.hpp"

#include <map>

namespace xe {
    static const std::map<InputStatus, std::string> s_inputStatusStr = {
        {InputStatus::Unknown, "InputStatus::Unknown"}, 
        {InputStatus::Release, "InputStatus::Release"}, 
        {InputStatus::Press, "InputStatus::Press"}, 
        {InputStatus::Push, "InputStatus::Push"}, 
        {InputStatus::Pop, "InputStatus::Pop"},
    };

    std::string toString(const InputStatus status) {
        const auto statusIt = s_inputStatusStr.find(status);
        return statusIt->second;
    }
}
