#ifndef GAME_H
#define GAME_H

#include <vector>

#include "renderer.h"

class Game
{
    public:
        enum class Direction {up, down, left, right};
        Game();
        void quit();
        void shiftBoard(Direction direction);
        int getScore() {return score;}
    private:
        void initializeBoard();
        bool isBoardFull();
        bool isGameOver();
        void spawnTile(int count);
        void startGameLoop();
        bool running;
        std::vector<std::vector<int>> board;
        Renderer *renderer;
        int score;

};

#endif