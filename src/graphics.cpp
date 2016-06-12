#include "graphics.h"
#include <SDL_Image.h>
Graphics::Graphics() {
}

Graphics::~Graphics() {
    this->terminate();
}

void Graphics::init(){
    SDL_CreateWindowAndRenderer(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "SDLPong");
}

void Graphics::terminate() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

