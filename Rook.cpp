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

    moved_ = false;
}



void Rook::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    int temp = 1;
    while (row - temp >= 0)
    {
        if (pieces_positions[row - temp][col] != nullptr)
        {
            if (pieces_positions[row - temp][col] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row - temp, col), _CAPTURE));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row - temp, col), _MOVE));
            temp++;
        }
    }

    temp = 1;
    while (row + temp < _BOARD_SIZE)
    {
        if (pieces_positions[row + temp][col] != nullptr)
        {
            if (pieces_positions[row + temp][col] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row + temp, col), _CAPTURE));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row + temp, col), _MOVE));
            temp++;
        }
    }

    temp = 1;
    while (col - temp >= 0)
    {
        if (pieces_positions[row][col - temp] != nullptr)
        {
            if (pieces_positions[row][col - temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row, col - temp), _CAPTURE));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row, col - temp), _MOVE));
            temp++;
        }
    }

    temp = 1;
    while (col + temp < _BOARD_SIZE)
    {
        if (pieces_positions[row][col + temp] != nullptr)
        {
            if (pieces_positions[row][col + temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row, col + temp), _CAPTURE));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row, col + temp), _MOVE));
            temp++;
        }
    }
}



void Rook::SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    int temp = 1;
    while (row - temp >= 0)
    {
        covering_squares_.push_back(make_pair(row - temp, col));
        if (pieces_positions[row - temp][col] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while (row + temp <_BOARD_SIZE)
    {
        covering_squares_.push_back(make_pair(row + temp, col));
        if (pieces_positions[row + temp][col] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while (col - temp >= 0)
    {
        covering_squares_.push_back(make_pair(row, col - temp));
        if (pieces_positions[row][col - temp] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while (col + temp < _BOARD_SIZE)
    {
        covering_squares_.push_back(make_pair(row, col + temp));
        if (pieces_positions[row][col + temp] != nullptr)
        {
            break;
        }

        temp++;
    }
}



//bool Rook::GetMoved() const
//{
//    return moved_;
//}



//Rook::~Rook()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

