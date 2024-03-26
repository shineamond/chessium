#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "MoveInformation.h"



class ChessBoard
{
    protected:
        ChessPiece* pieces_positions_[_BOARD_SIZE][_BOARD_SIZE];

    public:
        ~ChessBoard();
        virtual void DrawDefaultColorSquare(const int row, const int col) const = 0;
        void DrawClickedSquare(const int row, const int col) const;
        void DrawPiece(const int row, const int col) const;
        void DrawChessBoardAndPieces() const;

};
