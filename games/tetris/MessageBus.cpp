
#include "MessageBus.hpp"

#include <vector>

namespace tetris {

    class MessageBusImpl : public MessageBus {
    public:
        virtual void postMessage(const Message &message) override {
            m_pending.push_back(message);
        }

    private:
        std::vector<Message> m_pending;
    };

    std::unique_ptr<MessageBus> MessageBus::new_() {
        return std::make_unique<MessageBusImpl>();
    }
}
