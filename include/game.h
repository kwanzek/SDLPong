#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "graphics.h"
#include "globals.h"
#include "color.h"
#include "paddle.h"

struct Game {
    Game();
    ~Game();
    void init();
    void terminate();
    void gameLoop();

    Graphics* graphics = NULL;
    Paddle leftPaddle;
    Paddle rightPaddle;
    bool inProgress;
};

#endif
