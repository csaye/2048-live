#ifndef KEYINPUT_H
#define KEYINPUT_H

#include "game.h"

class KeyInput
{
    public:
        KeyInput(Game *game_);
        void process(SDL_Event &event);
    private:
        Game *game;
};

#endif