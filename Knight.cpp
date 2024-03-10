#include "Knight.h"



Knight::Knight()
{
    image_ = LoadTexture("media/black_knight.png");
    type_ = _KNIGHT;
}



Knight::~Knight()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}

