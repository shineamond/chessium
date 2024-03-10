#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"



class ChessBoard
{
    private:
        ChessPiece* pieces_positions_[_BOARD_SIZE][_BOARD_SIZE];

    public:
        ChessBoard();
        ~ChessBoard();
        void DrawChessBoard() const;
        void SetupBeginningBoard();
        void DrawPieces() const;
};
