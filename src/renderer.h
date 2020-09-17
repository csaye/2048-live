#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
    public:
        Renderer(int screenWidth, int screenHeight);
        ~Renderer();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif