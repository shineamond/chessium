#include "Knight.h"



Knight::Knight(const _CHESS_PIECE_COLORS color)
{
    type_ = _KNIGHT;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_knight.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_knight.png");
            break;
        default:
            image_ = nullptr;
    }
}



void Knight::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{

}



//Knight::~Knight()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

