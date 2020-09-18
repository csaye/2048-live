#include <iostream>

#include "renderer.h"

// const Color red(255, 0, 0, 255);
// const Color green(0, 255, 0, 255);
// const Color blue(0, 0, 255, 255);
// const Color white(255, 255, 255, 255);
// const Color black(0, 0, 0, 255);

Renderer::Renderer(int screenWidth_, int screenHeight_, int boardWidth_, int boardHeight_)
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;
    boardWidth = boardWidth_;
    boardHeight = boardHeight_;

    window = SDL_CreateWindow("2048 Live", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// void Renderer::clear()
// {
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);
// }

// void Renderer::drawRect(SDL_Rect rect, SDL_Color color)
// {
//     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//     SDL_RenderFillRect(renderer, &rect);
// }

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

    // clear();

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
    // SDL_RenderPresent(renderer);
}