#include "game.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>
#include <stdlib.h>

Game::Game() {}

Game::~Game() {}

void Game::init() {
    graphics = new Graphics();
    graphics->init();
    inProgress = true;

    this->createFonts();

    player1Score = 0;
    player2Score = 0;

    int middleLineWidth = 10;
    middleLine = SDL_Rect{Globals::SCREEN_WIDTH/2-middleLineWidth/2, 0, middleLineWidth, Globals::SCREEN_HEIGHT};

    player1ScoreRect = SDL_Rect{Globals::SCREEN_WIDTH/2-100, Globals::SCREEN_HEIGHT/8, 30, 30};
    player2ScoreRect = SDL_Rect{Globals::SCREEN_WIDTH/2+50, Globals::SCREEN_HEIGHT/8, 30, 30};

    whiteColor = SDL_Color{255,255,255};

    leftPaddle = new Paddle();
    leftPaddle->x = 0;
    leftPaddle->y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    leftPaddle->w = Globals::PADDLE_WIDTH;
    leftPaddle->h = Globals::PADDLE_HEIGHT;
    leftPaddle->collider = SDL_Rect{
        Globals::PADDLE_WIDTH-1,
        static_cast<int>(ceil(leftPaddle->y)),
        1,
        leftPaddle->h,
    };
    leftPaddle->paddleColor = Color{255,56,56,255};

    rightPaddle = new Paddle();
    rightPaddle->x = Globals::SCREEN_WIDTH-Globals::PADDLE_WIDTH;
    rightPaddle->y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    rightPaddle->w = Globals::PADDLE_WIDTH;
    rightPaddle->h = Globals::PADDLE_HEIGHT;
    rightPaddle->collider = SDL_Rect{
        Globals::SCREEN_WIDTH-Globals::PADDLE_WIDTH,
        static_cast<int>(ceil(rightPaddle->y)),
        1,
        rightPaddle->h,
    };
    rightPaddle->paddleColor = Color{0, 255, 188, 255};

    SDL_Surface* spriteSurface = IMG_Load("content/sprites/pongball.png");
    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(graphics->renderer, spriteSurface);
    //Transferring ownership to the Ball object
    ball = new Ball(Globals::SCREEN_WIDTH/2-10, Globals::SCREEN_HEIGHT/2-10, 1600, spriteSheet);
    SDL_FreeSurface(spriteSurface);
}

void Game::terminate() {
    delete graphics;
    inProgress = false;
}

void Game::gameLoop() {

    SDL_Event event;
    int currentTimeMS = SDL_GetTicks();
    int lastUpdateTimeMS = currentTimeMS;

    float dt = 0.01;
    float accumulator = 0.0f;

    bool upPressed = false;
    bool downPressed = false;
    while (inProgress) {

        lastUpdateTimeMS = currentTimeMS;
        currentTimeMS = SDL_GetTicks();
        float deltaTime = std::min((currentTimeMS - lastUpdateTimeMS) / 1000.0f, 0.016f);
        accumulator += deltaTime;

        while (accumulator >= dt) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                    inProgress = false;
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        upPressed = true;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        downPressed = true;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && !roundRunning) {
                        roundRunning = true;
                        startRound(*leftPaddle, *rightPaddle, *ball);
                    }
                }
                else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        upPressed = false;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        downPressed = false;
                    }
                }
            }
            //This split is done so that the paddle is moving smoothly from the moment you press down until you let go
            if (upPressed) {
                movePaddle(*leftPaddle, SDL_SCANCODE_UP, dt);
            }
            else if (downPressed) {
                movePaddle(*leftPaddle, SDL_SCANCODE_DOWN, dt);
            }
            accumulator -= dt;
        }

        SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 1);
        SDL_RenderClear(graphics->renderer);

        SDL_SetRenderDrawColor(graphics->renderer, 255, 255, 255, 1);
        SDL_RenderFillRect(graphics->renderer, &middleLine);
        SDL_RenderCopy(graphics->renderer, ball->spriteSheet, &ball->sourceRect, &ball->collider);

        //Draw Scores
        SDL_Surface* player1Message = TTF_RenderText_Solid(font, scoreMessage(player1Score).c_str(), whiteColor);
        SDL_Surface* player2Message = TTF_RenderText_Solid(font, scoreMessage(player2Score).c_str(), whiteColor);

        SDL_Texture* player1ScoreTexture = SDL_CreateTextureFromSurface(graphics->renderer, player1Message);
        SDL_Texture* player2ScoreTexture = SDL_CreateTextureFromSurface(graphics->renderer, player2Message);

        player1ScoreRect.w = player1Message->w;
        player1ScoreRect.h = player1Message->h;
        player1ScoreRect.x = Globals::SCREEN_WIDTH/2 - 200 - player1ScoreRect.w;
        player2ScoreRect.w = player2Message->w;
        player2ScoreRect.h = player2Message->h;
        player2ScoreRect.x = Globals::SCREEN_WIDTH/2 + 200;
        SDL_RenderCopy(graphics->renderer, player1ScoreTexture, NULL, &player1ScoreRect);
        SDL_RenderCopy(graphics->renderer, player2ScoreTexture, NULL, &player2ScoreRect);

        SDL_SetRenderDrawColor(graphics->renderer, leftPaddle->paddleColor.r, leftPaddle->paddleColor.g, leftPaddle->paddleColor.b, 1);
        SDL_Rect leftPaddleDrawRect = SDL_Rect{
            static_cast<int>(leftPaddle->x),
            static_cast<int>(leftPaddle->y),
            Globals::PADDLE_WIDTH,
            Globals::PADDLE_HEIGHT
        };
        SDL_RenderFillRect(graphics->renderer, &leftPaddleDrawRect);

        SDL_SetRenderDrawColor(graphics->renderer, rightPaddle->paddleColor.r, rightPaddle->paddleColor.g, rightPaddle->paddleColor.b, 1);
        SDL_Rect rightPaddleDrawRect = SDL_Rect{
            static_cast<int>(rightPaddle->x),
            static_cast<int>(rightPaddle->y),
            Globals::PADDLE_WIDTH,
            Globals::PADDLE_HEIGHT
        };

        SDL_RenderFillRect(graphics->renderer, &rightPaddleDrawRect);

        if (roundRunning) {
            //TODO: Swap with some rudimentary AI for controlling the second player
            rightPaddle->collider.y = ball->collider.y+10;
            if (ball->dx > 0) {
                detectPaddleCollision(*ball, *rightPaddle);
            }
            else {
                detectPaddleCollision(*ball, *leftPaddle);
            }
            detectWallCollision(*ball, deltaTime);
            moveBall(*ball, deltaTime);
        }

        SDL_RenderPresent(graphics->renderer);

        SDL_FreeSurface(player1Message);
        SDL_FreeSurface(player2Message);

        SDL_DestroyTexture(player1ScoreTexture);
        SDL_DestroyTexture(player2ScoreTexture);
    }
	this->terminate();
}

void Game::movePaddle(Paddle& paddle, SDL_Scancode keycode, float deltaTime) {
    if (keycode == SDL_SCANCODE_DOWN && paddle.y < (Globals::SCREEN_HEIGHT - Globals::PADDLE_HEIGHT)) {
        paddle.y += (deltaTime * Globals::PADDLE_SPEED);
    }
    else if (keycode == SDL_SCANCODE_UP && paddle.y > 0) {
        paddle.y -= (deltaTime * Globals::PADDLE_SPEED);
    }
    paddle.collider.y = static_cast<int>(ceil(paddle.y));
}

void Game::startRound(Paddle& player1, Paddle& player2, Ball& ball) {
    player1.y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    player1.collider.y = static_cast<int>(ceil(player1.y));

    player2.y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    player2.collider.y = static_cast<int>(ceil(player2.y));

    ball.x = Globals::SCREEN_WIDTH/2-40;
    ball.y = 0;
    ball.collider.x = static_cast<int>(ceil(ball.x));
    ball.collider.y = static_cast<int>(ceil(ball.y));

    int lastScored = 2;

    int angle = lastScored == 1 ? 45 : 135;

    //int randAngle = (rand() % 100) + 70; //Cone of degrees offset to place it between the two paddles
    ball.speed = 600.f;
    ball.dx = ball.speed * cos(degreesToRadians(angle));
    ball.dy = ball.speed * sin(degreesToRadians(angle));
}

void Game::moveBall(Ball& ball, float deltaTime) {
    if ( (ball.x > 0 && ball.dx < 0)
        || (ball.x < (Globals::SCREEN_WIDTH - ball.collider.w) && ball.dx > 0 ) ) {
        ball.x += (deltaTime * ball.dx);
    }
    if ( (ball.y > 0 && ball.dy < 0)
        || (ball.y < (Globals::SCREEN_HEIGHT - ball.collider.h) && ball.dy > 0) ) {
        ball.y += (deltaTime * ball.dy);
    }

    ball.collider.x = static_cast<int>(ceil(ball.x));
    ball.collider.y = static_cast<int>(ceil(ball.y));
}

void Game::detectPaddleCollision(Ball& ball, Paddle& paddle) {
    int ballLeft = ball.collider.x;
    int ballRight = ball.collider.x+ball.collider.w;
    int ballTop = ball.collider.y;
    int ballBottom = ball.collider.y + ball.collider.h;

    int paddleLeft = paddle.collider.x;
    int paddleRight = paddle.collider.x + paddle.collider.w;
    int paddleTop = paddle.collider.y;
    int paddleBottom = paddle.collider.y + paddle.collider.h;

    bool validCollision =
        (ball.collider.x + ball.collider.w/2 > paddle.collider.x && ball.dx < 0)
        || (ball.collider.x + ball.collider.w/2 < paddle.collider.x + Globals::PADDLE_WIDTH && ball.dx > 0);
    if (ballRight >= paddleLeft && ballLeft <= paddleRight && ballBottom >= paddleTop && ballTop <= paddleBottom  && validCollision) {
        //Need to detect where on the paddle the collision is, center, top or bottom

        if (ball.speed < ball.maxSpeed) {
            ball.speed += 40;
        }

        int paddleCenter = paddleTop + Globals::PADDLE_HEIGHT/2;
        //This approximates where the ball connects with the paddle close enough, using the closer Y axis
        int ballYIntersect = ballTop < paddleTop ? ballBottom : ballTop;

        int maxAngle = 70;
        int collisionDiff = ballYIntersect - paddleCenter; //Number from [-Globals::PADDLE_HEIGHT/2, Globals::PADDLE_HEIGHT/2]
        double normalized = collisionDiff / (Globals::PADDLE_HEIGHT/2.0); //Double from [-1,1]
        double bounceAngle = normalized * maxAngle;
        int direction = ball.dx < 0 ? 1 : -1;
        ball.dx = ball.speed * cos(degreesToRadians(bounceAngle)) * direction;
        ball.dy = ball.speed * sin(degreesToRadians(bounceAngle));
    }
}

void Game::detectWallCollision(Ball& ball, float deltaTime) {
    float deltaX = ball.x + (deltaTime * ball.x);
    float deltaY = ball.y + (deltaTime * ball.y);
    if (deltaX <= 0) {
        scorePoint(player2Score);
        lastScored = 2;
        resetRound();
    }
    else if (deltaX + ball.collider.w >= Globals::SCREEN_WIDTH) {
        scorePoint(player1Score);
        lastScored = 1;
        resetRound();
    }
    else if ((deltaY <= 0 && ball.dy < 0)  || (deltaY + ball.collider.h > Globals::SCREEN_HEIGHT && ball.dy > 0)) {
        ball.dy *= -1;
    }
}

void Game::scorePoint(int& playerScore) {
    playerScore++;
}

void Game::resetRound() {
    roundRunning = false;
    startRound(*leftPaddle, *rightPaddle, *ball);
}

void Game::createFonts() {
    font = TTF_OpenFont("content/fonts/FreeMono.ttf", 100);
}

double Game::degreesToRadians(int degrees) {
    return degrees * M_PI / 180.0;
}

std::string Game::scoreMessage(int playerScore) {
    std::stringstream ss;
    ss << playerScore;
    return ss.str();
}
