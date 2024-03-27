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
        _CHESS_PIECE_COLORS side_to_move_; // Temporary

    public:
        SpellChessBoard();
        void DrawDefaultColorSquare(const int row, const int col) const override;
        _MESSAGES_FROM_CHESSBOARD HandleGame();

};


