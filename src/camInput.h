#ifndef CAMINPUT_H
#define CAMINPUT_H

#include "game.h"

class CamInput
{
    public:
        CamInput(Game *game_);
        void process();
    private:
        Game *game;
};

#endif