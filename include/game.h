#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "graphics.h"
#include "globals.h"
#include "color.h"
#include "paddle.h"
#include "ball.h"

struct Game {
    Game();
    ~Game();
    void init();
    void terminate();
    void gameLoop();

    Graphics* graphics = NULL;
    Paddle* leftPaddle;
    Paddle* rightPaddle;
    Ball* ball;
    bool inProgress;

    void movePaddle(Paddle& paddle, SDL_Scancode keycode, float deltaTime);
};

#endif
