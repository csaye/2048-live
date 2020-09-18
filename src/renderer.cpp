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

void Renderer::loadImage(std::string name, SDL_Rect rect)
{
    std::string path = "../img/" + name + ".bmp";
    SDL_Surface *image = SDL_LoadBMP(path.c_str());
    if (image == NULL) std::cout << "Image " << name << " was not found.";
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

            switch (board[x][y])
            {
                case 2:
                    loadImage("2tile", rect);
                    break;
                case 4:
                    loadImage("4tile", rect);
                    break;
                case 8:
                    loadImage("8tile", rect);
                    break;
                case 16:
                    loadImage("16tile", rect);
                    break;
                case 32:
                    loadImage("32tile", rect);
                    break;
                case 64:
                    loadImage("64tile", rect);
                    break;
                case 128:
                    loadImage("128tile", rect);
                    break;
                case 256:
                    loadImage("256tile", rect);
                    break;
                case 512:
                    loadImage("512tile", rect);
                    break;
                case 1024:
                    loadImage("1024tile", rect);
                    break;
                case 2048:
                    loadImage("2048tile", rect);
                    break;
                case 4096:
                    loadImage("4096tile", rect);
                    break;
                case 8192:
                    loadImage("8192tile", rect);
                    break;
            }
        }
    }

    SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}