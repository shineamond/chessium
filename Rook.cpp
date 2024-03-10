#include "Rook.h"



Rook::Rook(const _CHESS_PIECE_COLORS color)
{
    type_ = _ROOK;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_rook.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_rook.png");
            break;
        default:
            image_ = nullptr;
    }
}



//Rook::~Rook()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

