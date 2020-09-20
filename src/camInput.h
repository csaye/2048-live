#ifndef CAMINPUT_H
#define CAMINPUT_H

#include "game.h"

class CamInput
{
    public:
        CamInput(Game *game_, int cameraNum);
        void process();
        void clear();
        void pause();
    private:
        Game *game;
        int cameraNum;
        int fps;
        void startProcess(int cameraNum);
        void calculateDirection(float x, float y);
        static void onMouse(int event, int x, int y, int, void*);
};

#endif