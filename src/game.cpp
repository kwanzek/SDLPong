#include "game.h"
#include <vector>

Game::Game() {}

Game::~Game() {}

void Game::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = new Graphics();
    inProgress = true;
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
        SDL_SetRenderDrawColor(graphics->renderer, 255, 128, 128, 1);

        SDL_Rect rect = SDL_Rect{100,100,100,100};
        SDL_RenderFillRect(graphics->renderer, &rect);

        SDL_RenderPresent(graphics->renderer);
    }
	this->terminate();
	SDL_Quit();
}
