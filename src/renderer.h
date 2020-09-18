#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

class Renderer
{
    public:
        Renderer(int screenWidth_, int screenHeight_, int boardWidth_, int boardHeight_);
        ~Renderer();
        void render(std::vector<std::vector<int>> &board);
    private:
        int screenWidth;
        int screenHeight;
        int boardWidth;
        int boardHeight;
        SDL_Window *window;
        SDL_Surface *surface;
        SDL_Renderer *renderer;
        
        // void clear();
        // void drawRect(SDL_Rect rect, SDL_Color color);
        void loadImage(std::string name, SDL_Rect rect);
};

#endif