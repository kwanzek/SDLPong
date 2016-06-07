#include "game.h"
#include <vector>

Game::Game() {}

Game::~Game() {}

void Game::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = new Graphics();
    inProgress = true;
    leftPaddle.collider = SDL_Rect{
        0,
        (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2),
        Globals::PADDLE_WIDTH,
        Globals::PADDLE_HEIGHT
    };
    leftPaddle.paddleColor = Color{255,56,56,255};
    rightPaddle.collider = SDL_Rect{
        Globals::SCREEN_WIDTH-Globals::PADDLE_WIDTH,
        (Globals::SCREEN_HEIGHT/2)-(Globals::PADDLE_HEIGHT/2),
        Globals::PADDLE_WIDTH,
        Globals::PADDLE_HEIGHT
    };
    rightPaddle.paddleColor = Color{0, 255, 188, 255};
}

void Game::terminate() {
    delete graphics;
    inProgress = false;
}

void Game::gameLoop() {

    SDL_Event event;
    while (inProgress) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                inProgress = false;
            }
        }
        SDL_SetRenderDrawColor(graphics->renderer, leftPaddle.paddleColor.r, leftPaddle.paddleColor.g, leftPaddle.paddleColor.b, 1);
        SDL_RenderFillRect(graphics->renderer, &leftPaddle.collider);

        SDL_SetRenderDrawColor(graphics->renderer, rightPaddle.paddleColor.r, rightPaddle.paddleColor.g, rightPaddle.paddleColor.b, 1);
        SDL_RenderFillRect(graphics->renderer, &rightPaddle.collider);

        SDL_RenderPresent(graphics->renderer);
    }
	this->terminate();
	SDL_Quit();
}
