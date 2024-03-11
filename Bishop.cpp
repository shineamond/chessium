#include "Bishop.h"



Bishop::Bishop(_CHESS_PIECE_COLORS color)
{
    type_ = _BISHOP;
    color_ = color;

    switch (color_)
    {
        case _BLACK:
            image_ = LoadTexture("media/black_bishop.png");
            break;
        case _WHITE:
            image_ = LoadTexture("media/white_bishop.png");
            break;
        default:
            image_ = nullptr;
    }
}



void Bishop::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{

}



//Bishop::~Bishop()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

