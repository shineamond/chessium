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

    moved_ = false;
}



void King::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (row - 1 >= 0)
    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row - 1][col - 1] != nullptr)
            {
                if (pieces_positions[row - 1][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col - 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col - 1), _MOVE));
            }
        }

        {
            if (pieces_positions[row - 1][col] != nullptr)
            {
                if (pieces_positions[row - 1][col] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col), _MOVE));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row - 1][col + 1] != nullptr)
            {
                if (pieces_positions[row - 1][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col + 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col + 1), _MOVE));
            }
        }
    }

    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row][col - 1] != nullptr)
            {
                if (pieces_positions[row][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row, col - 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row, col - 1), _MOVE));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row][col + 1] != nullptr)
            {
                if (pieces_positions[row][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row, col + 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row, col + 1), _MOVE));
            }
        }
    }

    if (row + 1 < _BOARD_SIZE)
    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row + 1][col - 1] != nullptr)
            {
                if (pieces_positions[row + 1][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col - 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col - 1), _MOVE));
            }
        }

        {
            if (pieces_positions[row + 1][col] != nullptr)
            {
                if (pieces_positions[row + 1][col] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col), _MOVE));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row + 1][col + 1] != nullptr)
            {
                if (pieces_positions[row + 1][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col + 1), _CAPTURE));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col + 1), _MOVE));
            }
        }
    }

//    if (moved_ == false)
//    {
//        if (pieces_positions[row][0] -> GetPieceType() == _ROOK)
//        {
//            if (pieces_positions[row][0] -> GetMoved() == false)
//            {
//
//            }
//        }
//    }
}



void King::SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    if (row - 1 >= 0)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row - 1, col - 1));
        }

        {
            covering_squares_.push_back(make_pair(row - 1, col));
        }

        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row - 1, col + 1));
        }
    }

    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row, col - 1));
        }

        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row, col + 1));
        }
    }

    if (row + 1 < _BOARD_SIZE)
    {
        if (col - 1 >= 0)
        {
            covering_squares_.push_back(make_pair(row + 1, col - 1));
        }

        {
            covering_squares_.push_back(make_pair(row + 1, col));
        }

        if (col + 1 < _BOARD_SIZE)
        {
            covering_squares_.push_back(make_pair(row + 1, col + 1));
        }
    }
}



//bool King::GetMoved() const
//{
//    return moved_;
//}



//King::~King()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

