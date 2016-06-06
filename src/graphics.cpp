#include "graphics.h"

Graphics::Graphics() {
    this->init();
}

Graphics::~Graphics() {
    this->terminate();
}

void Graphics::init(){
    SDL_CreateWindowAndRenderer(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "SDLPong");
}

void Graphics::terminate(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

