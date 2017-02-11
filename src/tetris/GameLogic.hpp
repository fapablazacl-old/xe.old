/*
    Tetris clone sample game.

    The game starts with the Main menu showed.

    This menus has the two follwing options:

    1. Start Game
    2. Exit

    The currently selected option is marked with a glow (or something like that), 
    and it's changed with the Up and Down arrow keys. 

    The Start Game option starts the game.
    The Exit option ends the game (without question).

    When the Game Starts, it shows the scenario of tetris, displaying the follwing parts:

    Frame*
    
                    .--------------------.
                    |   Game Field       |        Next Figure*
                    |    L               |        
                    |     L              |
                    |                    |        Remaining Time*
                    |                    |
                    .--------------------.

    The Frame its simply a big background image for decoration.
    The Game Field shows the current execution of the game.
    The Next Figure shows the next figure to be instanced before the current one lands.
    The Current Score shows the current score of the player.

    The logic of the game its the following:

    The Scenario is a grid of "empty" Blocks, with some of those Blocks already used.
    A Figure is a collection of Blocks that falls one block down at an game-defined time lapse. When it hits the bottom 
        of the scenario, or another block, it merge with the scenario, and a new Figure is spawned at the top center of the 
        scenario. When a figure is merged into the scenario, the game checks if a entire row of blocks is filled. If it is 
        the case, the entire row is detroyed. When a row of blocks is destroyed, the remaining ones that were stacked on top
        are moved one row down.

    The Player only can control a Figure at a Time, moving it left and right. The player can also accelerate the fall of the figure.

    The player Loses the Game when the current figure that hits the blocks of the scenario doesn't fill the scenario.
    The player Win the Game when the remaning time is gone.

    Use some just some basic lighting for code simplification.
*/

#pragma once 

#ifndef __tetris_gamelogic_hpp__
#define __tetris_gamelogic_hpp__

#include <memory>

namespace tetris {

    class MessageBus;

    class GameLogic {
    public:
        GameLogic();

        ~GameLogic();

        int run();

    private:
        std::unique_ptr<MessageBus> m_messageBus;
    };
}

#endif
