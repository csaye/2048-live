#ifndef CAMINPUT_H
#define CAMINPUT_H

#include "game.h"

class CamInput
{
    public:
        CamInput(Game *game_, int cameraNum, int fps_);
    private:
        Game *game;
        int fps;
        void startProcess(int cameraNum);
        void calculateDirection(float x, float y);
        static void onMouse(int event, int x, int y, int, void*);
};

#endif