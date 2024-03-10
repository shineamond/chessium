#include "Queen.h"



Queen::Queen()
{
    image_ = LoadTexture("media/black_queen.png");
    type_ = _QUEEN;
}



Queen::~Queen()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}

