#include <iostream>

#include "renderer.h"

Renderer::Renderer(int screenWidth_, int screenHeight_, int boardWidth_, int boardHeight_)
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;
    boardWidth = boardWidth_;
    boardHeight = boardHeight_;

    window = SDL_CreateWindow("2048 Live", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    drawBackground(50, 50, 50);

    surface = SDL_GetWindowSurface(window);

}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::drawBackground(int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

bool Renderer::isValidTile(int tile)
{
    if (tile < 2) return false;
    if (tile > 8192) return false;
    for (int i = tile; i > 2; i /= 2)
    {
        if (i % 2 != 0) return false;
    }
    return true;
}

void Renderer::loadTile(int tile, SDL_Rect rect)
{
    std::string path = "../img/" + std::to_string(tile) + "tile.bmp";
    SDL_Surface *image = SDL_LoadBMP(path.c_str());
    if (image == NULL) std::cout << "Image at path " << path << " not found.";
    SDL_BlitScaled(image, NULL, surface, &rect);
}

void Renderer::render(std::vector<std::vector<int>> &board)
{
    std::cout << "rendering\n";

    int w = screenWidth / boardWidth;
    int h = screenHeight / boardHeight;

    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[x].size(); y++)
        {
            SDL_Rect rect{x * w, y * h, w, h};
            int tile = board[x][y];
            if (isValidTile(tile)) loadTile(tile, rect);
        }
    }

    SDL_UpdateWindowSurface(window);
}