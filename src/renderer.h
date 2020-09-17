#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

struct Color
{
    Color(int r_, int g_, int b_, int a_)
    {
        if (r_ < 0) r = 0;
        else if (r_ > 255) r = 255;
        else r = r_;

        if (g_ < 0) g = 0;
        else if (g_ > 255) g = 255;
        else g = g_;

        if (b_ < 0) b = 0;
        else if (b_ > 255) b = 255;
        else b = b_;

        if (a_ < 0) a = 0;
        else if (a_ > 255) a = 255;
        else a = a_;
    }

    int r;
    int g;
    int b;
    int a;
};

class Renderer
{
    public:
        Renderer(int screenWidth, int screenHeight);
        ~Renderer();
        void render(std::vector<std::vector<int>> &board);
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif