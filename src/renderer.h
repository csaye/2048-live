#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

struct Rect
{
    Rect(int x_, int y_, int w_, int h_)
    {
        if (x_ < 0) x = 0;
        else x = x_;
        
        if (y_ < 0) y = 0;
        else y = y_;
        
        if (w_ < 0) w = 0;
        else w = w_;

        if (h_ < 0) h = 0;
        else h = h_;
    }

    int x;
    int y;
    int w;
    int h;
};

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
        Renderer(int screenWidth_, int screenHeight_, int boardWidth_, int boardHeight_);
        ~Renderer();
        void render(std::vector<std::vector<int>> &board);
    private:
        int screenWidth;
        int screenHeight;
        int boardWidth;
        int boardHeight;
        SDL_Window *window;
        SDL_Renderer *renderer;
        void clear();
        void drawRect(Rect rect, Color color);
};

#endif