#include "input.h"

Input::Input(Game *game_)
{
    game = game_;
}

void Input::process(SDL_Event &event)
{
    if (event.type == SDL_QUIT) game->quit();

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                game->shiftBoard(Direction::up);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                game->shiftBoard(Direction::down);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                game->shiftBoard(Direction::left);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                game->shiftBoard(Direction::right);
                break;
        }
    }
}