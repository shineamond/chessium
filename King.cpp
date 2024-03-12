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
    if (row - 1 >= 0)
    {
        if (col - 1 >= 0)
        {
            if (pieces_positions[row - 1][col - 1] != nullptr)
            {
                if (pieces_positions[row - 1][col - 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col - 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col - 1), "_MOVABLE"));
            }
        }

        {
            if (pieces_positions[row - 1][col] != nullptr)
            {
                if (pieces_positions[row - 1][col] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col), "_MOVABLE"));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row - 1][col + 1] != nullptr)
            {
                if (pieces_positions[row - 1][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row - 1, col + 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row - 1, col + 1), "_MOVABLE"));
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
                    possible_moves_.push_back(make_pair(make_pair(row, col - 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row, col - 1), "_MOVABLE"));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row][col + 1] != nullptr)
            {
                if (pieces_positions[row][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row, col + 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row, col + 1), "_MOVABLE"));
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
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col - 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col - 1), "_MOVABLE"));
            }
        }

        {
            if (pieces_positions[row + 1][col] != nullptr)
            {
                if (pieces_positions[row + 1][col] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col), "_MOVABLE"));
            }
        }

        if (col + 1 < _BOARD_SIZE)
        {
            if (pieces_positions[row + 1][col + 1] != nullptr)
            {
                if (pieces_positions[row + 1][col + 1] -> GetPieceColor() != color_)
                {
                    possible_moves_.push_back(make_pair(make_pair(row + 1, col + 1), "_TAKEABLE"));
                }
            }
            else
            {
                possible_moves_.push_back(make_pair(make_pair(row + 1, col + 1), "_MOVABLE"));
            }
        }
    }
}



//King::~King()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

