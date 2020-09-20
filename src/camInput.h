#ifndef CAMINPUT_H
#define CAMINPUT_H

#include "game.h"

class CamInput
{
    public:
        CamInput(Game *game_);
        void process(int cameraNum);
    private:
        Game *game;
        void calculateDirection(float x, float y);
        static void onMouse(int event, int x, int y, int, void*);
};

#endif