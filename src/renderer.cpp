#include "renderer.h"

Renderer::Renderer(int screenWidth, int screenHeight)
{
    window = SDL_CreateWindow("2048 Live", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawRect(int x, int y, int xSize, int ySize, Color color)
{

}

void Renderer::render(std::vector<std::vector<int>> &board)
{
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[x].size(); y++)
        {
            
        }
    }
}