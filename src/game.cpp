#include <thread>
#include <iostream>

#include "game.h"
#include "renderer.h"
#include "renderer.cpp"
#include "keyInput.h"
#include "keyInput.cpp"
#include "camInput.h"
#include "camInput.cpp"

const int screenWidth = 480;
const int screenHeight = 480;
const int boardWidth = 4;
const int boardHeight = 4;
const int fps = 100;
const int cameraNum = 0;

Game::Game()
{
    Renderer renderer_(screenWidth, screenHeight, boardWidth, boardHeight);
    renderer = &renderer_;
    startGameLoop();
}

void Game::quit()
{
    running = false;
    std::cout << "Game over.\n";
    std::cout << "Your score was: " << getScore() << "\n";
}

void Game::shiftBoard(Direction direction)
{
    std::cout << "shifting board\n";
    bool wasTileMoved = false;
    switch (direction)
    {
        case Direction::up:
        {
            for (int x = 0; x < boardWidth; x++)
            {
                for (int y = 1; y < boardHeight; y++)
                {
                    int tile = board[x][y];
                    if (tile == 0) continue;
                    int newY = y - 1;
                    int nextTile = board[x][newY];
                    if (nextTile != 0 && nextTile != tile) continue;
                    wasTileMoved = true;
                    
                    while (newY > 0)
                    {
                        if (board[x][newY] != 0) break;
                        newY--;
                    }
                    
                    board[x][y] = 0;
                    if (board[x][newY] == 0) board[x][newY] = tile;
                    else if (board[x][newY] == tile)
                    {
                        board[x][newY] = tile * 2;
                        score += (tile * 2);
                    }
                    else board[x][newY + 1] = tile;
                }
            }
            break;
        }
        case Direction::down:
        {
            for (int x = 0; x < boardWidth; x++)
            {
                for (int y = boardHeight - 2; y >= 0; y--)
                {
                    int tile = board[x][y];
                    if (tile == 0) continue;
                    int newY = y + 1;
                    int nextTile = board[x][newY];
                    if (nextTile != 0 && nextTile != tile) continue;
                    wasTileMoved = true;
                    
                    while (newY < boardHeight - 1)
                    {
                        if (board[x][newY] != 0) break;
                        newY++;
                    }
                    
                    board[x][y] = 0;
                    if (board[x][newY] == 0) board[x][newY] = tile;
                    else if (board[x][newY] == tile)
                    {
                        board[x][newY] = tile * 2;
                        score += (tile * 2);
                    }
                    else board[x][newY - 1] = tile;
                }
            }
            break;
        }
        case Direction::left:
        {
            for (int y = 0; y < boardHeight; y++)
            {
                for (int x = 1; x < boardWidth; x++)
                {
                    int tile = board[x][y];
                    if (tile == 0) continue;
                    int newX = x - 1;
                    int nextTile = board[newX][y];
                    if (nextTile != 0 && nextTile != tile) continue;
                    wasTileMoved = true;
                    
                    while (newX > 0)
                    {
                        if (board[newX][y] != 0) break;
                        newX--;
                    }
                    
                    board[x][y] = 0;
                    if (board[newX][y] == 0) board[newX][y] = tile;
                    else if (board[newX][y] == tile)
                    {
                        board[newX][y] = tile * 2;
                        score += (tile * 2);
                    }
                    else board[newX + 1][y] = tile;
                }
            }
            break;
        }
        case Direction::right:
        {
            for (int y = 0; y < boardHeight; y++)
            {
                for (int x = boardWidth - 2; x >= 0; x--)
                {
                    int tile = board[x][y];
                    if (tile == 0) continue;
                    int newX = x + 1;
                    int nextTile = board[newX][y];
                    if (nextTile != 0 && nextTile != tile) continue;
                    wasTileMoved = true;
                    
                    while (newX < boardWidth - 1)
                    {
                        if (board[newX][y] != 0) break;
                        newX++;
                    }
                    
                    board[x][y] = 0;
                    if (board[newX][y] == 0) board[newX][y] = tile;
                    else if (board[newX][y] == tile)
                    {
                        board[newX][y] = tile * 2;
                        score += (tile * 2);
                    }
                    else board[newX - 1][y] = tile;
                }
            }
            break;
        }
    }
    if (wasTileMoved)
    {
        spawnTile(1);
        renderer->render(board);
        renderer->setWindowTitle("2048 Live: score " + std::to_string(score));
    }
    if (isGameOver()) quit();
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

bool Game::isBoardFull()
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

bool Game::isGameOver()
{
    if (!isBoardFull()) return false;
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; y++)
        {
            int tile = board[x][y];
            if (x > 0 && board[x - 1][y] == tile) return false;
            if (x < boardWidth - 1 && board[x + 1][y] == tile) return false;
            if (y > 0 && board[x][y - 1] == tile) return false;
            if (y < boardHeight - 1 && board[x][y + 1] == tile) return false;
        }
    }
    return true;
}

void Game::spawnTile(int count)
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < count; i++)
    {
        if (isBoardFull()) return;

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
}

void Game::startGameLoop()
{
    score = 0;
    running = true;
    initializeBoard();
    renderer->render(board);

    SDL_Event event;
    CamInput camInput(this, cameraNum);
    KeyInput keyInput(this, &camInput);

    while (running)
    {
        camInput.process();
        while (SDL_PollEvent(&event)) keyInput.process(event);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}