#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"



class King : public ChessPiece
{
    private:

    public:
        King(const _CHESS_PIECE_COLORS color = _NONE);
        void SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]) override;
        void SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]);
        bool GetMoved() const;
        //~King();
};

