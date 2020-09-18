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
const int fps = 100;

Game::Game()
{
    Renderer renderer_(screenWidth, screenHeight, boardWidth, boardHeight);
    renderer = &renderer_;
    startGameLoop();
}

void Game::quit()
{
    running = false;
}

void Game::shiftBoard(Direction direction)
{
    switch (direction)
    {
        case Direction::up:
            break;
        case Direction::down:
            break;
        case Direction::left:
            break;
        case Direction::right:
            break;
    }
    spawnTile(1);
    // renderer->render(board);
}

void Game::initializeBoard()
{
    for (int x = 0; x < boardWidth; x++)
    {
        std::vector<int> col;
        for (int y = 0; y < boardHeight; y++) col.push_back(0);
        board.push_back(col);
    }
    spawnTile(2);
}

bool Game::boardFull()
{
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[x].size(); y++)
        {
            if (board[x][y] == 0) return false;
        }
    }
    return true;
}

void Game::spawnTile(int count)
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < count; i++)
    {
        if (boardFull()) return;

        int x = std::rand() % boardWidth;
        int y = std::rand() % boardHeight;
        // while (board[x][y] != 0)
        // {
        //     int x = std::rand() % boardWidth;
        //     int y = std::rand() % boardHeight;
        // }
        if (board[x][y] != 0)
        {
            for (int row = 0; row < boardWidth; row++)
            {
                for (int col = 0; col < boardHeight; col++)
                {
                    if (board[row][col] == 0)
                    {
                        x = row;
                        y = col;
                    }
                }
            }
        }

        board[x][y] = std::rand() % 2 == 0 ? 2 : 4;
    }
    renderer->render(board);
}

void Game::startGameLoop()
{
    initializeBoard();
    Input input(this);
    SDL_Event event;
    running = true;

    while (running)
    {
        while (SDL_PollEvent(&event)) input.process(event);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}