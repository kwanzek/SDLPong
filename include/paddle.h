#ifndef PADDLE_H
#define PADDLE_H

#include "color.h"

class Paddle {
public:
    inline Paddle(){};
    inline ~Paddle(){};

    SDL_Rect collider;
    Color paddleColor;
};
#endif // PADDLE_H
