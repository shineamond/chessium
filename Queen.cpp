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



void Queen::SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    // Bishop
    int temp = 1;
    while ((row - temp >= 0) && (col - temp >= 0))
    {
        if (pieces_positions[row - temp][col - temp] != nullptr)
        {
            if (pieces_positions[row - temp][col - temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row - temp, col - temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row - temp, col - temp), "_MOVABLE"));
            temp++;
        }
    }

    temp = 1;
    while ((row - temp >= 0) && (col + temp < _BOARD_SIZE))
    {
        if (pieces_positions[row - temp][col + temp] != nullptr)
        {
            if (pieces_positions[row - temp][col + temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row - temp, col + temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row - temp, col + temp), "_MOVABLE"));
            temp++;
        }
    }

    temp = 1;
    while ((row + temp < _BOARD_SIZE) && (col - temp >= 0))
    {
        if (pieces_positions[row + temp][col - temp] != nullptr)
        {
            if (pieces_positions[row + temp][col - temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row + temp, col - temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row + temp, col - temp), "_MOVABLE"));
            temp++;
        }
    }

    temp = 1;
    while ((row + temp < _BOARD_SIZE) && (col + temp < _BOARD_SIZE))
    {
        if (pieces_positions[row + temp][col + temp] != nullptr)
        {
            if (pieces_positions[row + temp][col + temp] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row + temp, col + temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row + temp, col + temp), "_MOVABLE"));
            temp++;
        }
    }

    //Rook
    temp = 1;
    while (row - temp >= 0)
    {
        if (pieces_positions[row - temp][col] != nullptr)
        {
            if (pieces_positions[row - temp][col] -> GetPieceColor() != color_)
            {
                possible_moves_.push_back(make_pair(make_pair(row - temp, col), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row - temp, col), "_MOVABLE"));
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
                possible_moves_.push_back(make_pair(make_pair(row + temp, col), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row + temp, col), "_MOVABLE"));
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
                possible_moves_.push_back(make_pair(make_pair(row, col - temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row, col - temp), "_MOVABLE"));
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
                possible_moves_.push_back(make_pair(make_pair(row, col + temp), "_TAKEABLE"));
            }

            break;
        }
        else
        {
            possible_moves_.push_back(make_pair(make_pair(row, col + temp), "_MOVABLE"));
            temp++;
        }
    }
}



//Queen::~Queen()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

