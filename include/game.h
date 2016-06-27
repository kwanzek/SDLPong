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
#include <string>

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
    bool roundRunning = false;

    int player1Score;
    int player2Score;
    int lastScored = 1;
    SDL_Rect middleLine;

    TTF_Font* font;
    SDL_Rect player1ScoreRect;
    SDL_Rect player2ScoreRect;
    SDL_Color whiteColor;

    void createFonts();
    void movePaddle(Paddle& paddle, SDL_Scancode keycode, float deltaTime);
    void startRound(Paddle& player1, Paddle& player2, Ball& ball);
    void detectPaddleCollision(Ball& ball, Paddle& paddle);
    void moveBall(Ball& ball, float deltaTime);
    void detectWallCollision(Ball& ball, float deltaTime);
    void scorePoint(int& playerScore);
    void resetRound();
    double degreesToRadians(int degrees);
    std::string scoreMessage(int playerScore);
};

#endif
