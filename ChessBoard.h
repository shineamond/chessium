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
        vector <pair <int, int>> clicked_squares_list_;

    public:
        ~ChessBoard();
        virtual void DrawDefaultColorSquare(const int row, const int col) const = 0;
        void DrawClickedSquare(const int row, const int col) const;
        void DrawPiece(const int row, const int col) const;
        void DrawChessBoardAndPieces() const;
        void PutPiece(const int row, const int col, const _CHESS_PIECE_TYPES type, const _CHESS_PIECE_COLORS color);
        void DestroyPiece(const int row, const int col);
        void DrawRelevantSquares(const int row, const int col, const _MOVE_TYPES move_type) const;

};
