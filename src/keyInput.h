#ifndef KEYINPUT_H
#define KEYINPUT_H

#include "game.h"
#include "camInput.h"

class KeyInput
{
    public:
        KeyInput(Game *game_, CamInput *camInput_) : game(game_), camInput(camInput_) {};
        void process(SDL_Event &event);
    private:
        Game *game;
        CamInput *camInput;
};

#endif