#ifndef BALL_H
#define BALL_H

#include "SDL.h"
class Ball {
public:
    inline Ball(){};
    inline Ball(float x, float y, SDL_Texture* spriteSheet) :
        x(x),
        y(y),
        spriteSheet(spriteSheet)
    {
        collider = SDL_Rect{
            static_cast<int>(x),
            static_cast<int>(y),
            80,
            80
        };
        sourceRect = SDL_Rect{0,0,80,80};
    }

    inline ~Ball(){}
    inline void terminate() {
        if (spriteSheet != nullptr)
        {
            SDL_DestroyTexture(spriteSheet);
            spriteSheet = nullptr;
        }
    }

    float x;
    float y;
    SDL_Texture* spriteSheet = nullptr;
    SDL_Rect collider;
    SDL_Rect sourceRect;
};
#endif // BALL_H
