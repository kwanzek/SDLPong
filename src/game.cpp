#include "game.h"
#include <vector>
#include <iostream>
#include <math.h>

Game::Game() {}

Game::~Game() {}

void Game::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = new Graphics();
    inProgress = true;

    leftPaddle.x = 0;
    leftPaddle.y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    leftPaddle.w = Globals::PADDLE_WIDTH;
    leftPaddle.h = Globals::PADDLE_HEIGHT;
    leftPaddle.collider = SDL_Rect{
        static_cast<int>(ceil(leftPaddle.x)),
        static_cast<int>(ceil(leftPaddle.y)),
        leftPaddle.w,
        leftPaddle.h,
    };
    leftPaddle.paddleColor = Color{255,56,56,255};

    rightPaddle.x = Globals::SCREEN_WIDTH-Globals::PADDLE_WIDTH;
    rightPaddle.y = (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2);
    rightPaddle.w = Globals::PADDLE_WIDTH;
    rightPaddle.h = Globals::PADDLE_HEIGHT;
    rightPaddle.collider = SDL_Rect{
        static_cast<int>(ceil(rightPaddle.x)),
        static_cast<int>(ceil(rightPaddle.y)),
        rightPaddle.w,
        rightPaddle.h,
    };
    rightPaddle.paddleColor = Color{0, 255, 188, 255};
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
            if (upPressed) {
                movePaddle(leftPaddle, SDL_SCANCODE_UP, dt);
            }
            else if (downPressed) {
                movePaddle(leftPaddle, SDL_SCANCODE_DOWN, dt);
            }
            accumulator -= dt;
        }

        SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 1);
        SDL_RenderClear(graphics->renderer);

        SDL_SetRenderDrawColor(graphics->renderer, leftPaddle.paddleColor.r, leftPaddle.paddleColor.g, leftPaddle.paddleColor.b, 1);
        SDL_RenderFillRect(graphics->renderer, &leftPaddle.collider);

        SDL_SetRenderDrawColor(graphics->renderer, rightPaddle.paddleColor.r, rightPaddle.paddleColor.g, rightPaddle.paddleColor.b, 1);
        SDL_RenderFillRect(graphics->renderer, &rightPaddle.collider);

        SDL_RenderPresent(graphics->renderer);
    }
	this->terminate();
	SDL_Quit();
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
