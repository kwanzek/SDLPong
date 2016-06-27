#ifndef BALL_H
#define BALL_H

#include "SDL.h"
class Ball {
public:
    inline Ball(){};
    inline Ball(float x, float y, float maxSpeed, SDL_Texture* spriteSheet) :
        x(x),
        y(y),
        maxSpeed(maxSpeed),
        spriteSheet(spriteSheet)
    {
        collider = SDL_Rect{
            static_cast<int>(x),
            static_cast<int>(y),
            20,
            20
        };
        sourceRect = SDL_Rect{0,0,80,80};
        speed = 0;
        dx = 0;
        dy = 0;
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
    float dx;
    float dy;
    float speed;
    float maxSpeed;
    SDL_Texture* spriteSheet = nullptr;
    SDL_Rect collider;
    SDL_Rect sourceRect;
};
#endif // BALL_H
