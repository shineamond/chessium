#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"



class Rook : public ChessPiece
{
    private:

    public:
        Rook(const _CHESS_PIECE_COLORS color = _COLORLESS);
        void SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]) override;
        void SetCoveringSquares(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]) override;
        bool GetMoved() const;
        //~Rook();
};

