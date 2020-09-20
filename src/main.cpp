// DEPENDENCIES:
// sdl2 (with homebrew: brew install sdl2)
// opencv (with homebrew: brew install opencv)

// COMPILE:
// g++ main.cpp -std=c++17 -lSDL2 `pkg-config --cflags --libs opencv4` -o 2048Live

#include <SDL2/SDL.h>

#include "game.h"
#include "game.cpp"

int main()
{
    Game game;
}