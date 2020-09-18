#ifndef GAME_H
#define GAME_H

#include <vector>

enum class Direction
{
    up,
    down,
    left,
    right
};

class Game
{
    public:
        Game();
        void quit();
        void triggerDirection(Direction direction);
    private:
        void initializeBoard();
        void startGameLoop();
        bool running;
        std::vector<std::vector<int>> board;
};

#endif