#include "game.h"
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main (int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) != (IMG_INIT_PNG|IMG_INIT_JPG)) {
        printf("Failed to initialize SDL_IMG: %s\n", IMG_GetError());
        return 0;
    }
    if (TTF_Init() != 0) {
        printf("Failed to initialize SDL_TTF: %s\n", TTF_GetError());
        return 0;
    }

    srand (time(NULL));

    Game game;
    game.init();
    game.gameLoop();
    SDL_Quit();

    return 0;
}
