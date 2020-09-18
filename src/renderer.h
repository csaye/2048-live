#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Renderer
{
    public:
        Renderer(int screenWidth_, int screenHeight_, int boardWidth_, int boardHeight_);
        ~Renderer();
        void render(std::vector<std::vector<int>> &board);
        void setWindowTitle(std::string title);
    private:
        int screenWidth;
        int screenHeight;
        int boardWidth;
        int boardHeight;
        SDL_Window *window;
        SDL_Surface *surface;
        bool isValidTile(int tile);
        void loadTile(int tile, SDL_Rect rect);
};

#endif