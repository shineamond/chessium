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

    moved_ = true;
}



void Pawn::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (color_ == _BLACK)
    {
        // Move
        if (row == 1)
        {
            if (pieces_positions[2][col] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(2, col), _MOVE));

                if (pieces_positions[3][col] == nullptr)
                {
                    possible_moves_.push_back(make_pair(make_pair(3, col), _MOVE));
                }
            }
        }
        else
        {
            if (pieces_positions[row + 1][col] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col), _MOVE));
            }
        }

        // Take
        if (row + 1 < _BOARD_SIZE)
        {
            if ((col - 1 >= 0) && (pieces_positions[row + 1][col - 1] != nullptr) && pieces_positions[row + 1][col - 1] -> GetPieceColor()== _WHITE)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col - 1), _CAPTURE));
            }

            if ((col + 1 < _BOARD_SIZE) && (pieces_positions[row + 1][col + 1] != nullptr) && pieces_positions[row + 1][col + 1] -> GetPieceColor() == _WHITE)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col + 1), _CAPTURE));
            }
        }
    }

    else if (color_ == _WHITE)
    {
        // Move
        if (row == 6)
        {
            if (pieces_positions[5][col] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(5, col), _MOVE));

                if (pieces_positions[4][col] == nullptr)
                {
                    possible_moves_.push_back(make_pair(make_pair(4, col), _MOVE));
                }
            }
        }
        else
        {
            if (pieces_positions[row - 1][col] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col), _MOVE));
            }
        }

        // Take
        if (row - 1 >= 0)
        {
            if ((col - 1 >= 0) && (pieces_positions[row - 1][col - 1] != nullptr) && pieces_positions[row - 1][col - 1] -> GetPieceColor() == _BLACK)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col - 1), _CAPTURE));
            }

            if ((col + 1 < _BOARD_SIZE) && (pieces_positions[row - 1][col + 1] != nullptr) && pieces_positions[row - 1][col + 1] -> GetPieceColor() == _BLACK)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col + 1), _CAPTURE));
            }
        }
    }
}



void Pawn::SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (color_ == _BLACK)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row + 1, col - 1));
        }
        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row + 1, col + 1));
        }
    }
    else if (color_ == _WHITE)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row - 1, col - 1));
        }
        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row - 1, col + 1));
        }
    }
}



//Pawn::~Pawn()
//{
//    type_ = _EMPTY;
//    color_ = _NONE;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}
