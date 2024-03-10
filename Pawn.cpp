#include "Pawn.h"



Pawn::Pawn()
{
    image_ = LoadTexture("media/black_pawn.png");
    type_ = _PAWN;
}



Pawn::~Pawn()
{
    type_ = _EMPTY;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}
