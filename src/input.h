#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include "game.h"

class Input
{
    public:
        Input(Game *game_);
        void process(SDL_Event &event);
    private:
        Game *game;
};

#endif