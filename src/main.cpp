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
    std::cout << "Welcome to 2048 live!\n";
    std::cout << "Left click and drag to select an object to track.\n";
    std::cout << "Press p to pause tracking and c to clear tracking.\n";
    Game game;
}