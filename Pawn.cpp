#include "Pawn.h"



Pawn::Pawn(const _CHESS_PIECE_COLORS color)
{
    type_ = _PAWN;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_pawn.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_pawn.png");
            break;
        default:
            image_ = nullptr;
    }
}



//Pawn::~Pawn()
//{
//    type_ = _EMPTY;
//    color_ = _NONE;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}
