#include "game.h"
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include <stdio.h>
int main (int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialize: %s\n", SDL_GetError());
        return 0;
    }
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

    Game game;
    game.init();
    game.gameLoop();
    SDL_Quit();

    return 0;
}
