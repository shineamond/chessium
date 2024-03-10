#include "Rook.h"



Rook::Rook()
{
    image_ = LoadTexture("media/black_rook.png");
    type_ = _ROOK;
}



Rook::~Rook()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}

