#include "Bishop.h"



Bishop::Bishop()
{
    image_ = LoadTexture("media/black_bishop.png");
    type_ = _BISHOP;
}



Bishop::~Bishop()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}

