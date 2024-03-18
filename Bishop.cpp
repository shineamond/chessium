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
}



void Bishop::SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    int temp = 1;
    while ((row - temp >= 0) && (col - temp >= 0))
    {
        covering_squares_.push_back(make_pair(row - temp, col - temp));
        if (pieces_positions[row - temp][col - temp] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while ((row - temp >= 0) && (col + temp < _BOARD_SIZE))
    {
        covering_squares_.push_back(make_pair(row - temp, col + temp));
        if (pieces_positions[row - temp][col + temp] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while ((row + temp < _BOARD_SIZE) && (col - temp >= 0))
    {
        covering_squares_.push_back(make_pair(row + temp, col - temp));
        if (pieces_positions[row + temp][col - temp] != nullptr)
        {
            break;
        }

        temp++;
    }

    temp = 1;
    while ((row + temp < _BOARD_SIZE) && (col + temp <_BOARD_SIZE))
    {
        covering_squares_.push_back(make_pair(row + temp, col + temp));
        if (pieces_positions[row + temp][col + temp] != nullptr)
        {
            break;
        }

        temp++;
    }
}



//Bishop::~Bishop()
//{
//    type_ = _EMPTY;
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}

