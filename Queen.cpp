#include "Queen.h"



Queen::Queen(const _CHESS_PIECE_COLORS color)
{
    type_ = _QUEEN;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_queen.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_queen.png");
            break;
        default:
            image_ = nullptr;
    }
}



//Queen::~Queen()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

