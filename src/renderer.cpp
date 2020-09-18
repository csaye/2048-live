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
    // std::string path = "testingPic.bmp";
    // SDL_Surface *image = SDL_LoadBMP(path.c_str());
    SDL_Surface *image = SDL_LoadBMP("test.bmp");
    if (image == NULL) std::cout << "null image";
    SDL_BlitSurface(image, &rect, surface, NULL);
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
                case 1:
                    // drawRect(rect, white);
                    loadImage("testingPic", rect);
                    break;
            }
        }
    }

    SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(renderer);
}