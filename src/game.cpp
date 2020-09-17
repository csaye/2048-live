#include "game.h"
#include "renderer.h"
#include "renderer.cpp"
#include "input.h"
#include "input.cpp"

const int screenWidth = 480;
const int screenHeight = 480;

Game::Game()
{
    startGameLoop();
}

void Game::quit()
{
    running = false;
}

void Game::startGameLoop()
{
    Renderer renderer(screenWidth, screenHeight);
    Input input(this);

    SDL_Event event;
    running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            input.process(event);
        }
    }
}