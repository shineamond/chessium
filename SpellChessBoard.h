#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "ChessBoard.h"



class SpellChessBoard : public ChessBoard
{
    private:

    public:
        SpellChessBoard();
        void DrawDefaultColorSquare(const int row, const int col) const override;

};


