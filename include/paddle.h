#ifndef PADDLE_H
#define PADDLE_H

#include "color.h"

class Paddle {
public:
    inline Paddle(){};
    inline ~Paddle(){};

    float x;
    float y;
    int w;
    int h;
    SDL_Rect collider;
    Color paddleColor;
};
#endif // PADDLE_H
