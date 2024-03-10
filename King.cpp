#include "King.h"



King::King()
{
    image_ = LoadTexture("media/black_king.png");
    type_ = _KING;
}



King::~King()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}

