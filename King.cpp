#include "King.h"



King::King(const _CHESS_PIECE_COLORS color)
{
    type_ = _KING;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_king.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_king.png");
            break;
        default:
            image_ = nullptr;
    }
}



void King::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{

}



//King::~King()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

