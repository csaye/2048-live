#include <thread>

#include "game.h"
#include "renderer.h"
#include "renderer.cpp"
#include "input.h"
#include "input.cpp"

const int screenWidth = 480;
const int screenHeight = 480;
const int boardWidth = 4;
const int boardHeight = 4;
const int fps = 2;

Game::Game()
{
    startGameLoop();
}

void Game::quit()
{
    running = false;
}

void Game::shiftBoard(Direction direction)
{
    // renderer.render(board);
}

void Game::initializeBoard()
{
    for (int x = 0; x < boardWidth; x++)
    {
        std::vector<int> col;
        for (int y = 0; y < boardHeight; y++) col.push_back(0);
        board.push_back(col);
    }
}

void Game::startGameLoop()
{
    Renderer renderer(screenWidth, screenHeight, boardWidth, boardHeight);
    Input input(this);

    initializeBoard();

    SDL_Event event;
    running = true;

    renderer.render(board);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            input.process(event);
        }

        renderer.render(board);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}