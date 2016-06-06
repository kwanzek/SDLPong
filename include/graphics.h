#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "globals.h"

class Graphics {
public:
    Graphics();
    ~Graphics();
    void init();
    void terminate();

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // GRAPHICS_H
