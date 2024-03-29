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

    moved_ = true;
}



void Knight::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (row - 2 >= 0)
    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row - 2][col - 1] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 2, col - 1), _MOVE));
            }
            else
            {
                if (pieces_positions[row - 2][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 2, col - 1), _CAPTURE));
                }
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row - 2][col + 1] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 2, col + 1), _MOVE));
            }
            else
            {
                if (pieces_positions[row - 2][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 2, col + 1), _CAPTURE));
                }
            }
        }
    }

    if (row - 1 >= 0)
    {
        if (col - 2 >= 0)
        {
            if (pieces_positions[row - 1][col - 2] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col - 2), _MOVE));
            }
            else
            {
                if (pieces_positions[row - 1][col - 2] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col - 2), _CAPTURE));
                }
            }
        }

        if (col + 2 < _BOARD_SIZE)
        {
            if (pieces_positions[row - 1][col + 2] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col + 2), _MOVE));
            }
            else
            {
                if (pieces_positions[row - 1][col + 2] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col + 2), _CAPTURE));
                }
            }
        }
    }

    if (row + 1 < _BOARD_SIZE)
    {
        if (col - 2 >= 0)
        {
            if (pieces_positions[row + 1][col - 2] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col - 2), _MOVE));
            }
            else
            {
                if (pieces_positions[row + 1][col - 2] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col - 2), _CAPTURE));
                }
            }
        }

        if (col + 2 < _BOARD_SIZE)
        {
            if (pieces_positions[row + 1][col + 2] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col + 2), _MOVE));
            }
            else
            {
                if (pieces_positions[row + 1][col + 2] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col + 2), _CAPTURE));
                }
            }
        }
    }

    if (row + 2 < _BOARD_SIZE)
    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row + 2][col - 1] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 2, col - 1), _MOVE));
            }
            else
            {
                if (pieces_positions[row + 2][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 2, col - 1), _CAPTURE));
                }
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row + 2][col + 1] == nullptr)
            {
                possible_moves_.push_back(make_pair(make_pair(row + 2, col + 1), _MOVE));
            }
            else
            {
                if (pieces_positions[row + 2][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 2, col + 1), _CAPTURE));
                }
            }
        }
    }
}



void Knight::SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (row - 2 >= 0)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row - 2, col - 1));
        }

        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row - 2, col + 1));
        }
    }

    if (row - 1 >= 0)
    {
        if (col - 2 >= 0)
        {
            covering_squares_.push_back(make_pair(row - 1, col - 2));
        }

        if (col + 2 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row - 1, col + 2));
        }
    }

    if (row + 1 < _BOARD_SIZE)
    {
        if (col - 2 >= 0)
        {
            covering_squares_.push_back(make_pair(row + 1, col - 2));
        }

        if (col + 2 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row + 1, col + 2));
        }
    }

    if (row + 2 < _BOARD_SIZE)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row + 2, col - 1));
        }

        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row + 2, col + 1));
        }
    }
}



//Knight::~Knight()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

