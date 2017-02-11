
#include "GameLogic.hpp"

#include "MessageBus.hpp"

namespace tetris {
    GameLogic::GameLogic() {
        m_messageBus = MessageBus::new_();
    }
    
    GameLogic::~GameLogic() {}

    int GameLogic::run() {
        return 0;
    }
}

int main(int argc, char **argv) {
    tetris::GameLogic gameLogic;

    return gameLogic.run();
}
