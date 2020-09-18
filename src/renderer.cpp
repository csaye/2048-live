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
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::drawRect(Rect rect, Color color)
{
    // std::cout << "rect at (" << rect.x << ", " << rect.y << ") of size (" << rect.w << ", " << rect.h << ")";

    SDL_Rect sdlRect{rect.x, rect.y, rect.w, rect.h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &sdlRect);
}

void Renderer::render(std::vector<std::vector<int>> &board)
{
    std::cout << "rendering\n";

    clear();

    int w = screenWidth / boardWidth;
    int h = screenHeight / boardHeight;

    Color black(0, 0, 0, 255);
    Color white(255, 255, 255, 255);

    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[x].size(); y++)
        {
            Rect rect(x * w, y * h, w, h);

            switch (board[x][y])
            {
                case 1:
                    drawRect(rect, white);
                    break;
            }
        }
    }

    SDL_RenderPresent(renderer);
}